# Godot 3.1 HMAC

## Status
Tested in Godot 3.1beta4 on macOS 10.14. Should work on all platforms.

This module is a wrapper around the MBEDTLS library.
You can validate/test your hashes using this online tool:
https://www.freeformatter.com/hmac-generator.html

## Install
- Clone this module and copy the hmac folder into your godot/modules folder
- Compile the engine or export template
- You now have a new object called HMAC

## Usage
### Instantiate new object
`var hmac = HMAC.new()`

### Initialize your new object
The initilization takes a PoolByteArray for each value. For strings, Godot can do this for you.
```
var key = "secret"
var payload = "Hello World"
hmac.init(key.to_utf8(), payload.to_utf8())
```

The default hash type is `sha256` but your other options are:
- none
- md2
- md4
- md5
- sha1
- sha224
- sha384
- sha512
- ripemd160

Pass the hash type as the last parameter in string format.

`hmac.init(key.to_utf8(), payload.to_utf8(), 'md5')`

### Generate a token
Run the digest function.
`hmac.digest()`

If you see no errors, you can print your HMAC with:
`print(hmac.get_hmac())`

*See Example project for more details*
