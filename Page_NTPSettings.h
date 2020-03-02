//
//  HTML PAGE
//

const char PAGE_NTPConfiguration[] PROGMEM = R"=====(
<title>TERMIKUS</title>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1" />
<div class="tiCen"><a href="admin.html" class="btn btn--m btn--blue">&uarr;</a>&nbsp;&nbsp;<strong>NTP Settings</strong></div>
<form action="" method="get">
<table class="cent">
<tr><td align="left" colspan="2"><hr></td></tr>
<tr><td colspan="2"><input type="checkbox" id="sfTm" name="sfTm"><input type="checkbox" id="sf" name="sf"><p id="warning" name="warning">&nbsp;</p></td></tr>
<tr><td align="right">NTP Server:</td><td><input type="text" id="ntpserver" name="ntpserver" maxlength="172" size="16"></td></tr>
<tr><td align="right">Refresh every:</td><td><input type="text" id="update" name="update" size="2" maxlength="4" value=""> min.(0=off)</td></tr>
<tr><td align="right">Time zone:</td><td>
<select  id="tz" name="tz" class="oth">
	<option value="-120">(GMT-12:00)</option>
	<option value="-110">(GMT-11:00)</option>
	<option value="-100">(GMT-10:00)</option>
	<option value="-90">(GMT-09:00)</option>
	<option value="-80">(GMT-08:00)</option>
	<option value="-70">(GMT-07:00)</option>
	<option value="-60">(GMT-06:00)</option>
	<option value="-50">(GMT-05:00)</option>
	<option value="-40">(GMT-04:00)</option>
	<option value="-35">(GMT-03:30)</option>
	<option value="-30">(GMT-03:00)</option>
	<option value="-20">(GMT-02:00)</option>
	<option value="-10">(GMT-01:00)</option>
	<option value="0">(GMT+00:00)</option>
	<option value="10">(GMT+01:00)</option>
	<option value="20">(GMT+02:00)</option>
	<option value="30">(GMT+03:00)</option>
	<option value="35">(GMT+03:30)</option>
	<option value="40">(GMT+04:00)</option>
	<option value="45">(GMT+04:30)</option>
	<option value="50">(GMT+05:00)</option>
	<option value="55">(GMT+05:30)</option>
	<option value="57">(GMT+05:45)</option>
	<option value="60">(GMT+06:00)</option>
	<option value="65">(GMT+06:30)</option>
	<option value="70">(GMT+07:00)</option>
	<option value="80">(GMT+08:00)</option>
	<option value="90">(GMT+09:00)</option>
	<option value="95">(GMT+09:30)</option>
	<option value="100">(GMT+10:00)</option>
	<option value="110">(GMT+11:00)</option>
	<option value="120">(GMT+12:00)</option>
	<option value="120">(GMT+12:00)</option>
	<option value="130">(GMT+13:00)</option>
</select>
</td></tr>
<tr><td align="right">Summer time:</td><td><label class="switch"><input type="checkbox" id="dst" name="dst"><span class="sliderBox"></span></label></td></tr>
<tr><td colspan="2"><hr></td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save" id="zapisz" disabled></td></tr>
</table>
</form>
<script>
var text = document.getElementById('warning');
var  sfTmCB = document.getElementById('sfTm');
var  sfCB = document.getElementById('sf');	

window.onload = function ()
{
	load("style.css","css", function() 
	{
		load("microajax.js","js", function() 
		{
				setValues("/admin/ntpvalues");
        setTimeout(warning1, 1000);
		});
	});
}

function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
function warning1(){ 
  if (sfTmCB.checked){
    text.style.display = "block";
    text.innerHTML = "To change NTP settings</br>disable the Safe Mode.";
    document.getElementById("zapisz").disabled = true;
    document.getElementById("ntpserver").disabled = true;
    document.getElementById("update").disabled = true;
    document.getElementById("tz").disabled = true;
    document.getElementById("dst").disabled = true;
  } else if (!sfCB.checked && !sfTmCB.checked){
    document.getElementById("zapisz").disabled = false;
  }
}
</script>
)=====";


void send_NTP_configuration_html()
{
   if (config.enableSafetyTemp){
    server.send ( 200, "text/html", PAGE_NTPConfiguration); 
    Serial.println(__FUNCTION__);
    return;
   }
  
	if (server.args() > 0 )  // Save Settings
	{
		config.daylight = false;
		String temp = "";
		for ( uint8_t i = 0; i < server.args(); i++ ) {
			if (server.argName(i) == "ntpserver") config.ntpServerName = urldecode( server.arg(i)); 
			if (server.argName(i) == "update") config.Update_Time_Via_NTP_Every =  server.arg(i).toInt(); 
			if (server.argName(i) == "tz") config.timezone =  server.arg(i).toInt(); 
			if (server.argName(i) == "dst") config.daylight = true; 
		}
		WriteConfig();
		firstStart = true;
	}
	server.send ( 200, "text/html", PAGE_NTPConfiguration ); 
	Serial.println(__FUNCTION__); 
	
}

void send_NTP_configuration_values_html()
{
		
	String values ="";
  values += "sf|" +   (String) (config.enableSafety ? "checked" : "") + "|chk\n";
  values += "sfTm|" +   (String) (config.enableSafetyTemp ? "checked" : "") + "|chk\n";
	values += "ntpserver|" + (String) config.ntpServerName + "|input\n";
	values += "update|" +  (String) config.Update_Time_Via_NTP_Every + "|input\n";
	values += "tz|" +  (String) config.timezone + "|input\n";
	values += "dst|" +  (String) (config.daylight ? "checked" : "") + "|chk\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__);
}
