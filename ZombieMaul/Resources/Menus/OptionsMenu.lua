local menu = {
    name = "Options Menu",
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
            x = 150.0,
            y = 350.0
        },
        scale = {
            x = 0.5,
            y = 0.5
        }
    },
    entries = {
        {
            text = "Music Volume: < 100 >",
            font = "Resources/Fonts/FreeSans.ttf",
            position = {
                x = 300.0,
                y = 400.0
            },
            scale = {
                x = 1.0,
                y = 1.0
            },
            onClick = function()
                cout("onClick Music Volume")
                return true
            end
        },
        {
            text = "Sfx Volume: < 100 >",
            font = "Resources/Fonts/FreeSans.ttf",
            position = {
                x = 300.0,
                y = 450.0
            },
            scale = {
                x = 1.0,
                y = 1.0
            },
            onClick = function()
                cout("onClick Sfx Volume")
                return true
            end
        },
        {
            text = "Exit",
            font = "Resources/Fonts/FreeSans.ttf",
            position = {
                x = 300.0,
                y = 500.0
            },
            scale = {
                x = 1.0,
                y = 1.0
            },
            onClick = function()
                game:popState()
                return true
            end
        }
    },
    onUpdate = function(self, curEntryIndex)
        --cout("onUpdate")
    end,
    onUpdateCurrentEntry = function(self, curEntryIndex)
        self:setIconPos(150.0, 350.0 + (curEntryIndex * 50.0))
    end
}

return menu
