package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"strconv"
	"strings"
	"sync"
)

type Item struct {
	ID   int                    `json:"id"`
	Data map[string]interface{} `json:"-"`
}

func (i Item) MarshalJSON() ([]byte, error) {
	m := make(map[string]interface{})
	m["id"] = i.ID
	for k, v := range i.Data {
		if k != "id" {
			m[k] = v
		}
	}
	return json.Marshal(m)
}

var (
	items   = make(map[int]Item)
	counter = 0
	mu      sync.RWMutex
)

func init() {
	for i := 1; i <= 1000; i++ {
		items[i] = Item{
			ID: i,
			Data: map[string]interface{}{
				"name":  fmt.Sprintf("Item %d", i),
				"value": float64(i),
			},
		}
	}
}

func main() {
	http.HandleFunc("/items", itemsHandler)
	http.HandleFunc("/items/", itemHandler)

	fmt.Println("Go Server listening on port 8081")
	http.ListenAndServe(":8081", nil)
}

func itemsHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")

	switch r.Method {
	case http.MethodGet:
		listItems(w)
	case http.MethodPost:
		createItem(w, r)
	default:
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
	}
}

func itemHandler(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")

	// Extract ID from path
	path := strings.TrimPrefix(r.URL.Path, "/items/")
	id, err := strconv.Atoi(path)
	if err != nil || id <= 0 {
		w.WriteHeader(http.StatusBadRequest)
		json.NewEncoder(w).Encode(map[string]string{"error": "Invalid ID"})
		return
	}

	switch r.Method {
	case http.MethodGet:
		getItem(w, id)
	case http.MethodPut:
		updateItem(w, r, id)
	case http.MethodDelete:
		deleteItem(w, id)
	default:
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
	}
}

func listItems(w http.ResponseWriter) {
	mu.RLock()
	defer mu.RUnlock()

	list := make([]Item, 0, len(items))
	for _, item := range items {
		list = append(list, item)
	}

	json.NewEncoder(w).Encode(list)
}

func createItem(w http.ResponseWriter, r *http.Request) {
	contentType := r.Header.Get("Content-Type")
	if !strings.Contains(contentType, "application/json") {
		w.WriteHeader(http.StatusBadRequest)
		json.NewEncoder(w).Encode(map[string]string{"error": "Content-Type must be application/json"})
		return
	}

	body, err := io.ReadAll(r.Body)
	if err != nil {
		w.WriteHeader(http.StatusBadRequest)
		json.NewEncoder(w).Encode(map[string]string{"error": "Failed to read body"})
		return
	}

	var data map[string]interface{}
	if err := json.Unmarshal(body, &data); err != nil {
		data = make(map[string]interface{})
	}

	mu.Lock()
	id := (counter % 1000) + 1
	counter++

	item := Item{ID: id, Data: data}
	items[id] = item
	mu.Unlock()

	json.NewEncoder(w).Encode(item)
}

func getItem(w http.ResponseWriter, id int) {
	mu.RLock()
	item, exists := items[id]
	mu.RUnlock()

	if !exists {
		json.NewEncoder(w).Encode(Item{
			ID: id,
			Data: map[string]interface{}{
				"name":  "",
				"value": float64(0),
			},
		})
		return
	}

	json.NewEncoder(w).Encode(item)
}

func updateItem(w http.ResponseWriter, r *http.Request, id int) {
	contentType := r.Header.Get("Content-Type")
	if !strings.Contains(contentType, "application/json") {
		w.WriteHeader(http.StatusBadRequest)
		json.NewEncoder(w).Encode(map[string]string{"error": "Content-Type must be application/json"})
		return
	}

	body, err := io.ReadAll(r.Body)
	if err != nil {
		w.WriteHeader(http.StatusBadRequest)
		json.NewEncoder(w).Encode(map[string]string{"error": "Failed to read body"})
		return
	}

	var data map[string]interface{}
	if err := json.Unmarshal(body, &data); err != nil {
		data = make(map[string]interface{})
	}

	mu.Lock()
	item := Item{ID: id, Data: data}
	items[id] = item
	mu.Unlock()

	json.NewEncoder(w).Encode(item)
}

func deleteItem(w http.ResponseWriter, id int) {
	mu.Lock()
	delete(items, id)
	mu.Unlock()

	json.NewEncoder(w).Encode(map[string]bool{"deleted": true})
}
