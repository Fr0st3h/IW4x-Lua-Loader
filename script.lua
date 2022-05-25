Debug:Print(os.date("%x", 906000490))
Utils:UI_PlaySound(0, "mp_ingame_summary", 0)
Utils:iPrintlnBold(0, "[^4LuaLoader^7] ^2Lua Loaded!")

cent = Structs:GetCentityIndex(1)

local startTimes =0
local curTime = 0

localClient = Structs:GetCClientIndex(1)
clientOne = Structs:GetCClientIndex(4)


local displayNotication = false

scroll = 0
isKeyDown = false

--Hud:TestSpawn()

local integer = 0

function notificationTest(title, message)
	if(Utils:CL_IsGameInitialized()) then
		Utils:Dvar_SetStringByName("com_errorMessage", message)
		Utils:Dvar_SetStringByName("com_errorTitle", title)
		Utils:Cbuf_AddText(0, "openmenu error_popmenu_lobby")
	end
end

function onKey(key)
	if(key.Type == EVENT_KEYDOWN) then
		if(key.KeyCode == KEY_LEFT) then
			isKeyDown = true
			startTimes = Utils:Sys_Millisecond()
			notificationTest("^5Lua Engine", "Lua Engine by Fr0st3h has been loaded")
		end
	elseif(key.Type == EVENT_KEYUP) then
		if(key.KeyCode == KEY_LEFT) then
			isKeyDown = false
		end
	end
	if(key.Type == EVENT_KEYDOWN) then
		if(key.KeyCode == KEY_DOWN) then
			if(scroll < 5) then
				scroll = scroll+1
				Utils:UI_PlaySound(0, "match_countdown_tick", 0)
			end
		elseif(key.KeyCode == KEY_UP) then
			if(scroll > 0) then
				scroll = scroll-1
				Utils:UI_PlaySound(0, "match_countdown_tick", 0)
			end
		end
	end
end

local blackBackground = true

function CL_DrawStretchPic(e)
	if(isKeyDown) then
		print(e.getShader)
	end
	if(blackBackground) then
		if(e.getShader == "mw2_main_background") then
			e:setMaterial("minimap_scanlines")
			e:setColor(10, 84, 245,255)
		elseif(e.getShader == "mockup_bg_glow") then
			e:setMaterial("minimap_scanlines")
			e:setColor(73, 10, 245,200)
		elseif(e.getShader == "mw2_main_cloud_overlay") then
			e:setMaterial("minimap_scanlines")
			e:setColor(0,0,0,200)
		elseif(e.getShader == "animbg_blur_front") then
			e:setColor(73, 10, 245,175)
		elseif(e.getShader == "logo_cod2") then
			e:setColor(0,0,0,0)
		elseif(e.getShader == "gradient_bottom") then
			e:setColor(0,0,0,125)
		end
	else
		if(e.getShader == "mw2_main_background") then
			e:setMaterial("minimap_scanlines")
			e:setColor(0, 255, 0,200)
		elseif(e.getShader == "mockup_bg_glow") then
			e:setMaterial("minimap_scanlines")
			e:setColor(255,0,0,200)
		elseif(e.getShader == "mw2_main_cloud_overlay") then
			e:setMaterial("minimap_scanlines")
			e:setColor(0,0,255,200)
		elseif(e.getShader == "animbg_blur_front") then
			e:setColor(0,0,255,200)
		elseif(e.getShader == "logo_cod2") then
			e:setColor(0,0,0,0)
		elseif(e.getShader == "gradient_bottom") then
			e:setColor(0,0,0,150)
		end
	end
end
--gradient_bottom

menuName = "Exodus v3"
font = "fonts/objectiveFont"

function drawNotification()
	local width = 1920
	local height = 1080
	local slideTime = 75

	local duration = 3000
	local startTime = startTimes
	local bHeight = 74

	local titleSize = 0.9
	local msgSize = 0.9

	local titleFont = "fonts/normalFont"
	local msgFont = "fonts/normalFont"

	height = height / 5
	height = height*4

if(Utils:Sys_Millisecond() < startTime or (startTime + duration) < Utils:Sys_Millisecond()) then
	--Debug:Print("Hit return")
	return

	elseif(Utils:Sys_Millisecond() - startTime < slideTime) then
		local diffH = height / 5
		local diff = Utils:Sys_Millisecond() - startTime
		local scale = 1.0 - ((1.0 * diff) / (1.0 * slideTime))
		diffH = (diffH * scale)
		height = height+diffH
	elseif(Utils:Sys_Millisecond() - startTime > (duration - slideTime)) then
		local diffH = height / 5
		local diff = (startTime + duration) - Utils:Sys_Millisecond()
		local scale = 1.0 - ((1.0 * diff) / (1.0 * slideTime))
		diffH = (diffH * scale)
		height = height+diffH
	end

	height = height + bHeight / 2
	bHeight = bHeight + (bHeight % 2)

	Drawing:drawShader(width / 2 - (225/2), (height - bHeight / 2)+50, 225, bHeight, 0,0,0,185)
	Drawing:drawShader(width / 2 - (225/2), (height - bHeight / 2)+50+69, (Utils:Sys_Millisecond() - startTime) / 13, 5, 255,0,0,255)
	Drawing:drawText("Lua Reloaded", width / 2 - (Drawing:GetTextWidth("Lua Reloaded", titleFont, titleSize)/2), (height - bHeight / 2)+99, titleFont, titleSize, 255,255,255,255)

end


function drawMenu() 
	drawNotification()
	Drawing:drawShader(25, 720/4, 300, 75, 33,33,33,255)--Title bar
	Drawing:drawShader(25, 720/4+75, 300, 350-115, 22,22,22,255)--Background
	Drawing:drawShader(25, 720/4+75, 300, 2, 0,180,255,255)--Top bar line
	Drawing:drawShader(25, 720/4+350-40, 300, 35, 33,33,33,255)--bottom bar
	Drawing:drawShader(25, 720/4+350-40, 300, 2, 0,180,255,255)--bottom bar line
	Drawing:drawText(menuName, (300/2)-(Drawing:GetTextWidth(menuName, font, 1.4)/2)+25, 240, font, 1.4, 0,180,255,255)
	Drawing:drawText("By Fr0st3h", 32, 250, "fonts/smallDevFont", 1.0, 255,255,255,255)
	
	--Drawing:drawText("^1LocalClient name: " .. localClient:GetName() .. " ^7Shooting: " .. (localClient) .. " Team: " .. localClient:GetTeam(), 50, 50, "fonts/objectiveFont", 0.7, 255,255,255,255)

	Drawing:drawMat(25, 273 + (35 * scroll),305, 30, 180, 0,180,255,255, "gradient_fadein")
	--Test

	Drawing:drawText("Main Mods Menu", 32, 295+(35*0), "fonts/objectiveFont", 0.45, 255,255,255,255)
	Drawing:drawText("Aimbot Menu", 32, 295+(35*1), "fonts/objectiveFont", 0.45, 255,255,255,255)
	Drawing:drawText("ESP Menu", 32, 295+(35*2), "fonts/objectiveFont", 0.45, 255,255,255,255)
	Drawing:drawText("Messages Menu", 32, 295+(35*3), "fonts/objectiveFont", 0.45, 255,255,255,255)
	Drawing:drawText("Settings Menu", 32, 295+(35*4), "fonts/objectiveFont", 0.45, 255,255,255,255)
	Drawing:drawText("Lua Menu", 32, 295+(35*5), "fonts/objectiveFont", 0.45, 255,255,255,255)
	

	for i = 0, 5, 1 do
		Drawing:drawMat(300, 278+(35*i), 18, 18, 0, 255,255,255,255, "hud_teamcaret")
	end
end

worldBulletPos = Vector3()
myPosScreen = Vector2(1920/2, 1080/2) 
local hovered = false
function ternary ( cond , T , F )
    if cond then return T else return F end
end

function menu_paintall()
	local screenBulletPos = Vector2()
	local headPosScreen = Vector3()
	drawNotification()
	for i = 1, 5, 1 do
	cent = Structs:GetCentityIndex(i)
	local clientOnePos = cent:GetOrigin()
	clientOne = Structs:GetCClientIndex(i)
	local myTeam = localClient:GetTeam()
		if(not Utils:EngineW2s(clientOnePos, screenBulletPos) or Utils:EngineW2s(clientOnePos, screenBulletPos)) then
			if(clientOne:GetTeam() == myTeam) then
				Drawing:drawText(clientOne:GetName(), screenBulletPos.X, screenBulletPos.Y, font, 0.4, 0,255,0,255)
			--	Drawing:drawShader(screenBulletPos.X/2, screenBulletPos.Y, 1920, 3, 255,0,0,255)
				Drawing:DrawLine(myPosScreen.X, myPosScreen.Y, screenBulletPos.X, screenBulletPos.Y, 0,255,0,255, 1.0)
			else
		--		Drawing:drawText(clientOne:GetName(), screenBulletPos.X, screenBulletPos.Y, font, 0.4, 255,0,0,255)
			--	Drawing:DrawLine(myPosScreen.X, myPosScreen.Y, screenBulletPos.X, screenBulletPos.Y, 255,0,0,255, 1.0)
			end
		end
	end


	drawMenu()

end

function bullet_hit(e)
	if(e.getEvent == 8339604) then
		worldBulletPos = Vector3(e.getPos.X, e.getPos.Y, e.getPos.Z)
	end

end

function obituary(o)
	local killerClientNum = o.getKillerClientNum
	local killerWeaponNum = o.getKillerWeaponNum
	local victimClientNum = o.getVictimClientNum
	local victimWeaponNum = o.getVictimWeaponNum
	local killType = o.getKillType

	local killer = Structs:GetCClientIndex(killerClientNum)
	local victim = Structs:GetCClientIndex(victimClientNum)
	local msg = "Client " .. killer:GetName() .. " ^7Killed Client " .. victim:GetName() .. " ^7Killtype was " .. killType
	Utils:iPrintlnBold(0, msg)

end

function onInit()
	startTimes = Utils:Sys_Millisecond()
	notificationTest("Lua Loader", "script.lua has been loaded")
end

function calculateNewX(origFontSize, origFont, newFont, text)
	local originalTextWidth = Drawing:GetTextWidth(text, origFont, origFontSize)
	local newTextWidth = Drawing:GetTextWidth(text, newFont, origFontSize)
	local newX = originalTextWidth - newTextWidth
	return newX
end



function UI_DrawTextHook(e)
	if(string.find(e.getText, "JOIN GAME")) then
		e:setFont("fonts/smallDevFont")
		e:setFontSize(2)
		e:setText("ONLINE")
		e:setY(e.getY-6)
		e:setX(e.getX-80)
		e:setColor(0,255,0,255)
	elseif(string.find(e.getText, "IW4x") and (e.getFont == "fonts/hudBigFont")) then
		e:setFont("fonts/hudBigFont")
		e:setX(e.getX-175)
		e:setY(e.getY+3)
		e:setText("Lua Engine")
		e:setColor(255,150,0,255)
	elseif(string.find(e.getText, "CHANGELOG")) then
		e:setColor(0,255,0,255)	
	elseif(string.find(e.getText, "CREATE A CLASS")) then
		e:setColor(255,0,0,255)	
	elseif(string.find(e.getText, "MODS")) then
		e:setColor(255,255,0,255)	
	end
end


Hooks:Register(HOOK_CG_OBITUARY, obituary)
Hooks:Register(HOOK_CL_DRAWSTRETCHPIC, CL_DrawStretchPic)
Hooks:Register(HOOK_CL_DRAWTEXTINTERNAL, UI_DrawTextHook)
Hooks:Register(HOOK_PREGAME_RENDER, menu_paintall)
Hooks:Register(HOOK_KEYBOARD, onKey)
Hooks:Register(HOOK_BULLETHITEVENT, bullet_hit)
onInit()

