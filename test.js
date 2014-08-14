'use strict';
var assert = require('assert');
var fullname = require('./');

it('should return the fullname of the current user', function () {
	console.log('Name:', fullname);
	assert.ok(typeof fullname === 'string');
	assert.ok(fullname.length > 0);
});
