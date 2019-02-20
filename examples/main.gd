extends Control
var hmac = HMAC.new()

func _ready():
	pass
	
func _cb_encrypt():
	hmac.init($panel/secret.text, $panel/payload.text, 6)
	hmac.digest()
	var hmacvalue = hmac.get_hmac()
	
	print(hmacvalue)

