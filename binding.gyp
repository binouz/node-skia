{
  'includes': [
    'config.gypi',
  ],
  'variables' : {
      'egl_platform': ''
  },
  'targets' : [
    {
      'target_name' : 'skia',
      'cflags': [
        '-std=c++11',
      ],
      'include_dirs' : [
        "<!(node -e \"require('nan')\")",
        'skia/include/animator',
        'skia/include/c',
        'skia/include/codec',
        'skia/include/config',
        'skia/include/core',
        'skia/include/device',
        'skia/include/effects',
        'skia/include/gpu',
        'skia/include/images',
        'skia/include/pathops',
        'skia/include/pipe',
        'skia/include/ports',
        'skia/include/private',
        'skia/include/svg',
        'skia/include/utils',
        'skia/include/views',
        'skia/include/xml',
        'skia/src/gpu',
      ],
      'link_settings': {
        'libraries': [
          '${PWD}/skia/out/Static/libskia.a',
          '-lEGL',
          '-lGLESv2',
          '-lfontconfig',
          '-lfreetype'
        ],
      },
      'sources' : [
        'src/init.cc',
        'src/SkiaWindow.cc',
        'src/SkiaCanvas.cc',
        'src/SkiaView.cc',
        'src/SkiaViewElement.cc',
        'src/SkiaViewStyle.cc',
        'src/EGLNativeInterface.cc',
      ],
      'conditions' : [
        [
          'egl_platform=="x11"',
          {
            'link_settings': {
              'libraries': [
                '-lX11'
              ]
            },
            'sources' : [
              'src/platforms/x11/EGLNativeInterfaceX11.cc'
            ]
          }
        ],
        [
          'egl_platform=="fbdev"',
          {
            'link_settings': {
              'libraries': [
                # TODO
              ]
            },
            'sources' : [
              'src/platforms/fbdev/EGLNativeInterfaceFbdev.cc'
            ]
          }
        ]
      ]
    },
  ],
}
