# Lost at C

In this repo we will build a web application in C. Not a web server, a web application. It will be experimental (what else) and this readme serves as the log/stream of consciousness.

It will use as much C as possible, and as little JavaScript as possible. The C will be compiled to WebAssembly (wasm). It will not use any existing runtime or memory management libraries.

## Gathering materials for the raft

To compile to wasm, we use clang with target `wasm32`. A simple function is exported to test the setup

```c
int square(int x) {
    return x * x;
}
```

The build script

```bash
clang --target=wasm32 -c -O1 -o app.o app1.c
wasm-ld-8 --no-entry --export square -o app.wasm app.o

```

I can't get it to work without the intermediate step: clang fails to find `wasm-ld-8`.

Finally, loading the wasm in html

```html
<html>
  <head>
    <meta charset="utf-8" />
    <style>
      body {
        margin: 0px;
      }
    </style>
  </head>

  <body>
    <script>
      WebAssembly.instantiateStreaming(fetch("./app.wasm"), {}).then(
        (result) => {
          const {
            instance: {
              exports: { memory, square },
            },
          } = result;

          console.log(square(4));
        }
      );
    </script>
  </body>
</html>
```

This should log `16` to the console. If it doesn't log a number, look for an error message. If it logs some different number, throw your computer out the window.

_we are now at `app1.c`_

## Seeing if it will float at all

Let us return some html from C. Yeah, you heard me.
