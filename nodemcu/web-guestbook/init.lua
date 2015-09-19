wifi.setmode(wifi.STATION);
wifi.sta.config("TP-LINK", "1234567890");
wifi.sta.connect();
tmr.alarm(1, 1000, 1, function()
    if wifi.sta.getip() == nil then
        print("Wating...")
    else
        tmr.stop(1)
        print("IP is "..wifi.sta.getip())
        dofile("server.lua")
    end
end)
