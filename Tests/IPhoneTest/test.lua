
function luagame:Init()
	self.GameIdent = "Our awesome testgame!"
	self.GameVersion = "1.0"
	
	--testvec = luagame.vec2.new()
	--print("testvec: " .. testvec:tostring())
	--print("testvec.instance: " .. tostring(testvec.instance))
	
	---------------------------------------------------------
	-- Fail guard test for "class" member calling.
	--testvec.instance = 123
	--print("Should fail now: " .. testvec:tostring())
	---------------------------------------------------------
	
	--print("luagame.vec2.ToString(): " .. luagame.vec2.ToString())
	
	screenw, screenh = luagame.graphics.getscreensize()
	print("Screen size: " .. tostring(screenw) .. "x" .. tostring(screenh))
	
	testani = 0.0
end

function luagame:PreLoad()
	print("Time to PRELOAD some data!")
	-- TODO: Does not work, at all.
	--       Should add resources that need to be loaded. LuaGame should then
	--       iterate over them and load them into a resource/data pool of some sort.
end

function luagame:Update(dt)
	--print("Time to UPDATE our game with '" .. tostring(dt) .. "'")
	testani = testani + dt
end

function luagame:Render()
	--print("Time to RENDER our game!")
	
	luagame.graphics.drawquad(100+math.cos(testani)*10, 100+math.sin(testani)*10, 20, 20)
	luagame.graphics.drawquad(50+math.cos(testani+23)*10, 100+math.sin(testani+23)*10, 20, 20)
	luagame.graphics.drawquad(100+math.cos(testani+45)*10, 50+math.sin(testani+12)*10, 20, 20)
	
	luagame.graphics.rotate((2.0*3.14) / 123.0)
	luagame.graphics.drawquad(100, 200, 30, 30)
	--luagame.graphics.rotate(0.0)
	luagame.graphics.translate(math.cos(testani)*20, math.sin(testani)*10)
	luagame.graphics.drawquad(100, 200, 30, 30)
	
	for i=1,100 do
	 luagame.graphics.drawquad(100, 200+(i*3), 100, 2)
	end
	--luagame.graphics.drawquad(10, 10, 40, 40)
end