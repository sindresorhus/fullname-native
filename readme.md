# fullname-native [![Build Status](https://travis-ci.org/sindresorhus/fullname-native.svg?branch=master)](https://travis-ci.org/sindresorhus/fullname-native)

> Get the fullname of the current user


## Install

```bash
$ npm install --save fullname-native
```

**This is a [native binding](http://nodejs.org/api/addons.html) and expects you to have the required [toolchain](https://github.com/TooTallNate/node-gyp#installation).** *(ignore the node-gyp install)*

Tested to work on OS X and Windows.


## Usage

```js
var fullname = require('fullname-native');

console.log(fullname);
//=> Sindre Sorhus
```


## CLI

You can also use it as a CLI app by installing it globally:

```bash
$ npm install --global fullname-native
```

#### Usage

```bash
$ fullname --help

Usage
  $ fullname
  Sindre Sorhus
```


## License

[MIT](http://opensource.org/licenses/MIT) © [Sindre Sorhus](http://sindresorhus.com)
