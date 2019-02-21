extends Control
var hmac = HMAC.new()

func _ready():
	pass
	
func _cb_encrypt():
	hmac.init($panel/secret.text.to_utf8(), $panel/payload.text.to_utf8(), $panel/hash_type.text)
	hmac.digest()
	print(str("Your HMAC: ", hmac.get_hmac()))
	$panel/result.text = hmac.get_hmac()