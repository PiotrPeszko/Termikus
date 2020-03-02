//
//   The HTML PAGE
//

const char PAGE_Information[] PROGMEM = R"=====(
<title>TERMIKUS</title>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1" />
<div class="tiCen"><a href="admin.html" class="btn btn--m btn--blue">&uarr;</a>&nbsp;&nbsp;<strong>Network Review</strong></div>
<hr>
<table class="cent">
<tr><td align="right">SSID:</td><td><span id="x_ssid"></span></td></tr>
<tr><td align="right">IP:</td><td><span id="x_ip"></span></td></tr>
<tr><td align="right">Netmask:</td><td><span id="x_netmask"></span></td></tr>
<tr><td align="right">Gateway:</td><td><span id="x_gateway"></span></td></tr>
<tr><td align="right">MAC:</td><td><span id="x_mac"></span></td></tr>
<tr><td colspan="2"><hr></span></td></tr>
<tr><td align="right">NTP Time:</td><td><span id="x_ntp"></span></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<tr><td colspan="2" align="center"><a href="javascript:GetState()" class="btn btn--m btn--blue">REFRESH</a></td></tr>
</table>
<script>

function GetState()
{
	setValues("/admin/infovalues");
}
window.onload = function ()
{
	load("style.css","css", function() 
	{
		load("microajax.js","js", function() 
		{
				GetState();
		});
	});
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
)=====" ;


//
// FILL WITH INFOMATION
// 

void send_information_values_html ()
{

	String values ="";

	values += "x_ssid|" + (String)WiFi.SSID() +  "|div\n";
	values += "x_ip|" +  (String) WiFi.localIP()[0] + "." +  (String) WiFi.localIP()[1] + "." +  (String) WiFi.localIP()[2] + "." + (String) WiFi.localIP()[3] +  "|div\n";
	values += "x_gateway|" +  (String) WiFi.gatewayIP()[0] + "." +  (String) WiFi.gatewayIP()[1] + "." +  (String) WiFi.gatewayIP()[2] + "." + (String) WiFi.gatewayIP()[3] +  "|div\n";
	values += "x_netmask|" +  (String) WiFi.subnetMask()[0] + "." +  (String) WiFi.subnetMask()[1] + "." +  (String) WiFi.subnetMask()[2] + "." + (String) WiFi.subnetMask()[3] +  "|div\n";
	values += "x_mac|" + GetMacAddress() +  "|div\n";
	values += "x_ntp|" +  (String) DateTime.hour + ":" + (String) + DateTime.minute +  ":"  + (String)  DateTime.second + " " + (String)   DateTime.year + "-" + (String)  DateTime.month + "-" + (String)  DateTime.day +  "|div\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__);
}
