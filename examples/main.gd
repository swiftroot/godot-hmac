extends Control
var hmac = HMAC.new()

func _ready():
	pass
	
func _cb_encrypt():
	hmac.init("AWS4wGDVl360ipsuvqrAvNMQNMsgYKHdi1Mq5xjYCnhl".to_utf8(), "20190411T020944Z".to_utf8(), "sha256")
	#hmac.init($panel/secret.text.to_utf8(), $panel/payload.text.to_utf8(), $panel/hash_type.text)
	hmac.digest()
	print(str("Your HMAC: ", hmac.get_hmac()))
	$panel/result.text = hmac.get_hmac()
	
	