{
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
          '-lX11',
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
        'src/EGLNativeBackend.cc',
      ],
    },
  ],
}
