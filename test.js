import test from 'ava';
import m from './';

test(t => {
	console.log('Fullname:', m);
	t.is(typeof m, 'string');
	t.true(m.length > 0);
});
