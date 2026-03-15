-- wrk Lua script for POST /items with JSON body
wrk.method = "POST"
wrk.headers["Content-Type"] = "application/json"

local counter = 0

request = function()
    counter = counter + 1
    local id = (counter % 1000) + 1
    local body = string.format('{"name":"Item %d","value":%d}', id, id)
    return wrk.format(nil, nil, nil, body)
end
