-- wrk Lua script for DELETE /items/{id}
wrk.method = "DELETE"

local counter = 0

request = function()
    counter = counter + 1
    local id = (counter % 10000) + 1
    return wrk.format(nil, "/items/" .. id, nil, nil)
end
