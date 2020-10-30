var assert = require('assert');
var daemon = require('..');

assert.throws(() => {daemon.daemonize(1, 2, 3)});
assert.throws(() => {daemon.daemonize(true, true, true)});
assert.throws(() => {daemon.daemonize(1, 2)});
assert.throws(() => {daemon.daemonize(true, 2)});
assert.throws(() => {daemon.daemonize(1, true)});

daemon.daemonize(true, true);

throw "Exception in daemon";