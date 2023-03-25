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
        cout("curEntryIndex " .. curEntryIndex)
        if curEntryIndex == 0 then

        end
    end
}

return menu
