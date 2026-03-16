package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"strconv"
	"strings"
	"sync"
	"sync/atomic"
)

type Item struct {
	ID    int    `json:"id"`
	Name  string `json:"name"`
	Value int    `json:"value"`
}

var (
	items   = make(map[int]Item)
	counter atomic.Int64
	mu      sync.RWMutex
)

func init() {
	for i := 1; i <= 1000; i++ {
		items[i] = Item{
			ID:    i,
			Name:  fmt.Sprintf("Item %d", i),
			Value: i,
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
	list := make([]Item, 0, len(items))
	for _, item := range items {
		list = append(list, item)
	}
	mu.RUnlock()

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

	var data Item
	if err := json.Unmarshal(body, &data); err != nil {
		data = Item{}
	}

	c := counter.Add(1)
	id := int((c-1)%1000) + 1
	data.ID = id

	mu.Lock()
	items[id] = data
	mu.Unlock()

	json.NewEncoder(w).Encode(data)
}

func getItem(w http.ResponseWriter, id int) {
	mu.RLock()
	item, exists := items[id]
	mu.RUnlock()

	if !exists {
		json.NewEncoder(w).Encode(Item{ID: id})
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

	var data Item
	if err := json.Unmarshal(body, &data); err != nil {
		data = Item{}
	}
	data.ID = id

	mu.Lock()
	items[id] = data
	mu.Unlock()

	json.NewEncoder(w).Encode(data)
}

func deleteItem(w http.ResponseWriter, id int) {
	mu.Lock()
	delete(items, id)
	mu.Unlock()

	json.NewEncoder(w).Encode(map[string]bool{"deleted": true})
}
