#!/usr/bin/env node
'use strict';
var meow = require('meow');
var fullname = require('./');

meow({
	help: [
		'Example',
		'  fullname',
		'  Sindre Sorhus'
	].join('\n')
});

console.log(fullname);
