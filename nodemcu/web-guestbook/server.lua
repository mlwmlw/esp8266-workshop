srv=net.createServer(net.TCP)
srv:listen(80,function(conn)
    conn:on("receive", function(client,request)
        local buf = "";
        local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP");
        if(method == nil)then
            _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP");
        end
        local _GET = {}
        if (vars ~= nil)then
            for k, v in string.gmatch(vars, "(%w+)=(%w+)&*") do
                _GET[k] = v
            end
        end
        buf = buf.."<h1>ESP8266 Web Server</h1>";
        buf = buf.."<form method=\"GET\">";
        buf = buf.."leave a message: <input type=\"text\" name=\"msg\" />";
        buf = buf.."<input type=\"submit\" />";
        buf = buf.."</form>";
				if(_GET.msg ~= nil)then
					i2c.setup(0, 2, 1, i2c.SLOW)
					lcd = dofile("lcd1602.lua")(0x20)
					lcd.put(lcd.locate(0, 0), _GET.msg);
				end
        client:send(buf);
        client:close();
        collectgarbage();
    end)
end)
