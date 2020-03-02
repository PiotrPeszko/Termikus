//
//  HTML PAGE
//
const char PAGE_NetworkConfiguration[] PROGMEM = R"=====(
<title>TERMIKUS</title>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1" />
<div class="tiCen"><a href="admin.html" class="btn btn--m btn--blue">&uarr;</a>&nbsp;&nbsp;<strong>WiFi Configuration</strong></div>
<form action="" method="get">
<table class="cent">
<tr><td align="left" colspan="2"><hr></td></tr>
<tr><td colspan="2"><input type="checkbox" id="sfTm" name="sfTm"><input type="checkbox" id="sf" name="sf"><p id="warning" name="warning">&nbsp;</p></td></tr>
<tr><td align="right">SSID:</td><td><input type="text" id="ssid" name="ssid" size="18"></td></tr>
<tr><td align="right">Password:</td><td><input type="password" id="password" name="password" size="18"></td></tr>
<tr><td align="right">DHCP:</td><td><label class="switch"><input type="checkbox" id="dhcp" name="dhcp"><span class="sliderBox"></span></label></td></tr>
<tr><td align="right">IP:</td><td><input type="text" id="ip_0" name="ip_0" size="1">.<input type="text" id="ip_1" name="ip_1" size="1">.<input type="text" id="ip_2" name="ip_2" size="1">.<input type="text" id="ip_3" name="ip_3" value=""  size="1"></td></tr>
<tr><td align="right">Netmask:</td><td><input type="text" id="nm_0" name="nm_0"  size="1">.<input type="text" id="nm_1" name="nm_1"  size="1">.<input type="text" id="nm_2" name="nm_2"  size="1">.<input type="text" id="nm_3" name="nm_3"  size="1"></td></tr>
<tr><td align="right">Gateway:</td><td><input type="text" id="gw_0" name="gw_0"  size="1">.<input type="text" id="gw_1" name="gw_1"  size="1">.<input type="text" id="gw_2" name="gw_2"  size="1">.<input type="text" id="gw_3" name="gw_3"  size="1"></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<tr><td align="left" colspan="2"><hr></td></tr>
<tr><td colspan="2" align="center"><input type="submit" class="btn btn--m btn--blue" value="Save" name="zapisz" id="zapisz" style="width:150px" disabled></td></tr>
</table>
</form>
<hr>&nbsp;&nbsp;<strong>WiFi Status:</strong><div id="connectionstate">N/A</div><hr>
&nbsp;&nbsp;<strong>Networks:</strong><br>
<table class="cent">
<tr><td><div id="networks">Skanning WiFi...</div></td></tr>
<tr><td align="center"><a href="javascript:GetState()" style="width:130px" class="btn btn--m btn--blue">REFRESH</a></td></tr>
</table>
<script>
var text = document.getElementById('warning');
var  sfTmCB = document.getElementById('sfTm');
var  sfCB = document.getElementById('sf');

function GetState()
{
	setValues("/admin/connectionstate");
}
function selssid(value)
{
	document.getElementById("ssid").value = value; 
}
window.onload = function ()
{
	load("style.css","css", function() 
	{
		load("microajax.js","js", function() 
		{
					setValues("/admin/values");
					setTimeout(GetState,3000);
          setTimeout(warning1,1000);
		});
	});
}

function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

function warning1(){ 
  if (sfCB.checked && sfTmCB.checked || !sfCB.checked && sfTmCB.checked){
    text.style.display = "block";
    text.innerHTML = "To change network configuration</br>disable the Safe Mode first.";
    document.getElementById("zapisz").disabled = true;
    document.getElementById("ssid").disabled = true;
    document.getElementById("password").disabled = true;
    document.getElementById("dhcp").disabled = true;
  }  else if (!sfCB.checked && !sfTmCB.checked){
    document.getElementById("zapisz").disabled = false;
  }
}
</script>
)=====";

const char PAGE_WaitAndReload[] PROGMEM = R"=====(
<meta http-equiv="refresh" content="5; URL=config.html">
<span style="font-size: 16px">Please Wait.... Configuring and Restarting.</span>
)=====";


//
//  SEND HTML PAGE OR IF A FORM SUMBITTED VALUES, PROCESS THESE VALUES
// 

void send_network_configuration_html()
{
	  if (config.enableSafetyTemp){
    server.send ( 200, "text/html", PAGE_NetworkConfiguration); 
    Serial.println(__FUNCTION__);
    return;
   }
	if (server.args() > 0 )  // Save Settings
	{
		String temp = "";
		config.dhcp = false;
		for ( uint8_t i = 0; i < server.args(); i++ ) {
			if (server.argName(i) == "ssid") config.ssid =   urldecode(server.arg(i));
			if (server.argName(i) == "password") config.password =    urldecode(server.arg(i)); 
			if (server.argName(i) == "ip_0") if (checkRange(server.arg(i))) 	config.IP[0] =  server.arg(i).toInt();
			if (server.argName(i) == "ip_1") if (checkRange(server.arg(i))) 	config.IP[1] =  server.arg(i).toInt();
			if (server.argName(i) == "ip_2") if (checkRange(server.arg(i))) 	config.IP[2] =  server.arg(i).toInt();
			if (server.argName(i) == "ip_3") if (checkRange(server.arg(i))) 	config.IP[3] =  server.arg(i).toInt();
			if (server.argName(i) == "nm_0") if (checkRange(server.arg(i))) 	config.Netmask[0] =  server.arg(i).toInt();
			if (server.argName(i) == "nm_1") if (checkRange(server.arg(i))) 	config.Netmask[1] =  server.arg(i).toInt();
			if (server.argName(i) == "nm_2") if (checkRange(server.arg(i))) 	config.Netmask[2] =  server.arg(i).toInt();
			if (server.argName(i) == "nm_3") if (checkRange(server.arg(i))) 	config.Netmask[3] =  server.arg(i).toInt();
			if (server.argName(i) == "gw_0") if (checkRange(server.arg(i))) 	config.Gateway[0] =  server.arg(i).toInt();
			if (server.argName(i) == "gw_1") if (checkRange(server.arg(i))) 	config.Gateway[1] =  server.arg(i).toInt();
			if (server.argName(i) == "gw_2") if (checkRange(server.arg(i))) 	config.Gateway[2] =  server.arg(i).toInt();
			if (server.argName(i) == "gw_3") if (checkRange(server.arg(i))) 	config.Gateway[3] =  server.arg(i).toInt();
			if (server.argName(i) == "dhcp") config.dhcp = true;
		}
		server.send ( 200, "text/html", PAGE_WaitAndReload );
		WriteConfig();
		ConfigureWifi();
		AdminTimeOutCounter=0;   
	}
	else
	{
		server.send ( 200, "text/html", PAGE_NetworkConfiguration ); 
	}
	Serial.println(__FUNCTION__); 
}

//
//   FILL THE PAGE WITH VALUES
//

void send_network_configuration_values_html()
{

	String values ="";
  values += "sf|" +   (String) (config.enableSafety ? "checked" : "") + "|chk\n";
  values += "sfTm|" +   (String) (config.enableSafetyTemp ? "checked" : "") + "|chk\n";
	values += "ssid|" + (String) config.ssid + "|input\n";
	values += "password|" +  (String) config.password + "|input\n";
	values += "ip_0|" +  (String) config.IP[0] + "|input\n";
	values += "ip_1|" +  (String) config.IP[1] + "|input\n";
	values += "ip_2|" +  (String) config.IP[2] + "|input\n";
	values += "ip_3|" +  (String) config.IP[3] + "|input\n";
	values += "nm_0|" +  (String) config.Netmask[0] + "|input\n";
	values += "nm_1|" +  (String) config.Netmask[1] + "|input\n";
	values += "nm_2|" +  (String) config.Netmask[2] + "|input\n";
	values += "nm_3|" +  (String) config.Netmask[3] + "|input\n";
	values += "gw_0|" +  (String) config.Gateway[0] + "|input\n";
	values += "gw_1|" +  (String) config.Gateway[1] + "|input\n";
	values += "gw_2|" +  (String) config.Gateway[2] + "|input\n";
	values += "gw_3|" +  (String) config.Gateway[3] + "|input\n";
	values += "dhcp|" +  (String) (config.dhcp ? "checked" : "") + "|chk\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__); 
	
}


//
//   FILL THE PAGE WITH NETWORKSTATE & NETWORKS
//

void send_connection_state_values_html()
{

	String state = "N/A";
	String Networks = "";
	if (WiFi.status() == 0) state = "Idle";
	else if (WiFi.status() == 1) state = "NO SSID AVAILBLE";
	else if (WiFi.status() == 2) state = "SCAN COMPLETED";
	else if (WiFi.status() == 3) state = "CONNECTED";
	else if (WiFi.status() == 4) state = "CONNECT FAILED";
	else if (WiFi.status() == 5) state = "CONNECTION LOST";
	else if (WiFi.status() == 6) state = "DISCONNECTED";
   int n = WiFi.scanNetworks();
	 if (n == 0)
	 {
		 Networks = "<font color='#FF0000'>No WiFi network found!</font>";
	 }
	else
    {
		Networks = String(n) + " networks found.<br>";
		Networks += "<table border='0' cellspacing='0' cellpadding='3'>";
		Networks += "<tr bgcolor='#DDDDDD' ><td><strong>Name</strong></td><td><strong>Quality</strong></td><td><strong>Enc</strong></td><tr>";
		for (int i = 0; i < n; ++i)
		{
			int quality=0;
			if(WiFi.RSSI(i) <= -100)
			{
					quality = 0;
			}
			else if(WiFi.RSSI(i) >= -50)
			{
					quality = 100;
			}
			else
			{
				quality = 2 * (WiFi.RSSI(i) + 100);
			}
			Networks += "<tr><td><a href='javascript:selssid(\""  +  String(WiFi.SSID(i))  + "\")'>"  +  String(WiFi.SSID(i))  + "</a></td><td>" +  String(quality) + "%</td><td>" +  String((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*")  + "</td></tr>";
		}
		Networks += "</table>";
	}
   
	String values ="";
	values += "connectionstate|" + state + "|div\n";
	values += "networks|" +  Networks + "|div\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__); 
	
}
