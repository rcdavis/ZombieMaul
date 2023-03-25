local menu = {
    name = "Main Menu",
    background = {
        texture = "Resources/Textures/MenuBG1.png",
        position = {
            x = 0.0,
            y = -20.0
        },
        scale = {
            x = 0.8,
            y = 0.75
        }
    },
    icon = {
        texture = "Resources/Textures/MenuPointer.png",
        position = {
            x = 80.0,
            y = 240.0
        },
        scale = {
            x = 0.8,
            y = 0.8
        }
    },
    entries = {
        {
            texture = "Resources/Textures/MenuPlay.png",
            position = {
                x = 280.0,
                y = 220.0
            },
            scale = {
                x = 1.0,
                y = 1.0
            },
            onClick = function()
                cout("onClick Play")
            end
        },
        {
            texture = "Resources/Textures/MenuOptions.png",
            position = {
                x = 260.0,
                y = 260.0
            },
            scale = {
                x = 0.6,
                y = 0.6
            },
            onClick = function()
                cout("onClick Options")
            end
        },
        {
            texture = "Resources/Textures/MenuCredits.png",
            position = {
                x = 250.0,
                y = 330.0
            },
            scale = {
                x = 0.6,
                y = 0.6
            },
            onClick = function()
                cout("onClick Credits")
            end
        },
        {
            texture = "Resources/Textures/MenuExit.png",
            position = {
                x = 310.0,
                y = 440.0
            },
            scale = {
                x = 0.8,
                y = 0.8
            },
            onClick = function()
                cout("onClick Exit")
            end
        }
    },
    onUpdate = function(self, curEntryIndex)
        --cout("onUpdate")
    end,
    onUpdateCurrentEntry = function(self, curEntryIndex)
        if (curEntryIndex == 0) then
            self:setIconPos(80.0, 240.0)

            self:setEntryPos(0, 280.0, 220.0)
            self:setEntryScale(0, 1.0, 1.0)

            self:setEntryPos(1, 260.0, 260.0)
            self:setEntryScale(1, 0.6, 0.6)

            self:setEntryPos(2, 250.0, 330.0)
            self:setEntryScale(2, 0.6, 0.6)

            self:setEntryPos(3, 310.0, 440.0)
            self:setEntryScale(3, 0.8, 0.8)
        elseif (curEntryIndex == 1) then
            self:setIconPos(5.0, 300.0)

            self:setEntryPos(0, 300.0, 230.0)
            self:setEntryScale(0, 0.8, 0.8)

            self:setEntryPos(1, 200.0, 200.0)
            self:setEntryScale(1, 0.8, 0.8)

            self:setEntryPos(2, 250.0, 330.0)
            self:setEntryScale(2, 0.6, 0.6)

            self:setEntryPos(3, 310.0, 440.0)
            self:setEntryScale(3, 0.8, 0.8)
        elseif (curEntryIndex == 2) then
            self:setIconPos(5.0, 350.0)

            self:setEntryPos(0, 300.0, 230.0)
            self:setEntryScale(0, 0.8, 0.8)

            self:setEntryPos(1, 260.0, 240.0)
            self:setEntryScale(1, 0.6, 0.6)

            self:setEntryPos(2, 210.0, 260.0)
            self:setEntryScale(2, 0.8, 0.8)

            self:setEntryPos(3, 310.0, 440.0)
            self:setEntryScale(3, 0.8, 0.8)
        elseif (curEntryIndex == 3) then
            self:setIconPos(80.0, 440.0)

            self:setEntryPos(0, 300.0, 230.0)
            self:setEntryScale(0, 0.8, 0.8)

            self:setEntryPos(1, 260.0, 260.0)
            self:setEntryScale(1, 0.6, 0.6)

            self:setEntryPos(2, 250.0, 330.0)
            self:setEntryScale(2, 0.6, 0.6)

            self:setEntryPos(3, 300.0, 420.0)
            self:setEntryScale(3, 1.0, 1.0)
        end
    end
}

return menu
