import test from 'ava';
import x from './';

test(t => {
	console.log('Fullname:', x);
	t.is(typeof x, 'string');
	t.true(x.length > 0);
	t.end();
});
