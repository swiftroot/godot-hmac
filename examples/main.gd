extends Control
var hmac = HMAC.new()

func _ready():
	var hello = "String"
	hello.to_utf8()
	
func _cb_encrypt():
	hmac.init($panel/secret.text.to_utf8(), $panel/payload.text.to_utf8(), 6)
	hmac.digest()
	var hmacvalue = hmac.get_hmac()
	print("Local print")
	print(hmacvalue)

