{
    'conditions': [
        [
            'OS=="linux"',
            {
                'targets': [
                    {
                        'target_name': 'rpi_ws281x_node',
                        'sources': [
                            './src/module.c',
                            './src/driver.c',
                            './src/rpi_hw.c',
                            './src/channel.c',
                        ],
                        'dependencies': ['rpi_ws281x'],
                        'include_dirs': ['./lib/jgarff/rpi_ws281x'],
                    },
                    {
                        'target_name': 'rpi_ws281x',
                        'type': 'static_library',
                        'sources': [
                            './lib/jgarff/rpi_ws281x/ws2811.c',
                            './lib/jgarff/rpi_ws281x/pwm.c',
                            './lib/jgarff/rpi_ws281x/dma.c',
                            './lib/jgarff/rpi_ws281x/mailbox.c',
                            './lib/jgarff/rpi_ws281x/rpihw.c',
                            './lib/jgarff/rpi_ws281x/pcm.c'
                        ]
                    }
                ]
            },
            {
                'targets': [
                    {
                        'target_name': 'rpi_ws281x_node',
                        'type': 'none',
                        'actions': [
                            {
                                'action_name': 'unsupported_platform',
                                'inputs': [],
                                'outputs': ['no_build'],
                                'action': ['true'],
                                'message': 'Package is being installed on an unsupported platform.'
                            }
                        ]
                    }
                ]
            }
        ]
    ]
}
