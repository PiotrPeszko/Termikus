//
//  HTML PAGE
//
const char PAGE_AdminGeneralSettings[] PROGMEM =  R"=====(
<title>TERMIKUS</title>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1" />
<div class="tiCen"><a href="admin.html"  class="btn btn--m btn--blue">&uarr;</a>&nbsp;&nbsp;<strong>Basic Settings:</strong></div>
<form action="" method="get">
<table class="cent">
<tr><td colspan="2"><td></td>
<tr><td colspan="2"><input type="checkbox" id="sf" name="sf"><input type="checkbox" id="sfTm" name="sfTm"><p id="warning" name="warning">&nbsp;</p></td></tr>
<tr><td align="left" colspan="2"><hr></td></tr>
<tr><td align="right">Device name:</td><td><input type="text" id="devicename" name="devicename" size="12"></td></tr>
<tr><td align="right">Device number:</td><td><select id="devicenumber" name="devicenumber"><option value="0">0</option><option value="1">1</option><option value="2">2</option><option value="3">3</option><option value="4">4</option><option value="5">5</option><option value="6">6</option><option value="7">7</option><option value="8">8</option><option value="9">9</option><option value="9">10</option></select></td></tr>
<tr><td colspan="2" align="center"><input type="checkbox" id="sfTm" name="sfTm"><span id="warning" name="warning">&nbsp;</span></td></tr>
<tr><td align="left" colspan="2"><hr></td></tr>
<tr><td align="right">Main temperature:</td><td><input type="text" id="baseTemp" name="baseTemp" size=3></td></tr>
<tr><td><br></td></tr>
<tr><td class="slidecontainer" colspan=2><input type="range" min="0" max="35" value="" step="0.5" class="slider" id="myRange"></td></tr>
<tr><td align="left" colspan="2"><hr></td></tr><tr><td align="right">Sensor resolution:</td><td><select id="ds_resolution" name="ds_resolution"><option value="9">0.50&deg;C</option><option value="10">0.25&deg;C</option><option value="11">0.125&deg;C</option><option value="12">0.0625&deg;C</option></select></td></tr>
<tr><td align="right">Upper histeresis:</td><td><input type="text" id="histG" name="histG" size="5" value="0.5" min="0"></tr>
<tr><td align="right">Lower histeresis:</td><td><input type="text" id="histD" name="histD" size="5" value="0.5" min="0"></tr>
<tr><td align="right">Cooling mode:</td><td><label class="switch"><input type="checkbox" id="cool" name="cool"><span class="sliderBox"></span></label></td></tr>
<tr><td align="left" colspan="2"><hr></td></tr>
<tr><td align="right">API write:</td><td><label class="switch"><input type="checkbox" id="API" name="API"><span class="sliderBox"></span></label></td></tr>
<tr><td align="left" colspan="2"><hr></td></tr><tr><td align="center" colspan="2"><strong>ThingSpeak:</strong></td></tr>
<tr><td align="right">Enable:</td><td><label class="switch"><input type="checkbox" id="sendTh" name="sendTh"><span class="sliderBox"></span></label></td></tr>
<tr><td align="right">Server address:</td><td><input type="text" id="hostServerName" name="hostServerName" size="14"></td></tr>
<tr><td align="right">Channel number:</td><td><input type="text" id="hostChannelNumber" name="hostChannelNumber" size="14"></td></tr>
<tr><td align="right">Write code:</td><td><input type="text" id="hostWriteKey" name="hostWriteKey" size="14"></td></tr>
<tr><td align="right">Report period:</td><td><input type="text" id="hostUpdatePeriod" name="hostUpdatePeriod" size="3" value=""></td></tr>
<tr><td align="left" colspan="2"><hr></td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save" id="zapisz"></td></tr>
</table>
</form>

<script>
var text = document.getElementById('warning');
var  sfTmCB = document.getElementById('sfTm');
var  sfCB = document.getElementById('sf');

var slider = document.getElementById("myRange");
var output = document.getElementById("baseTemp");
output.value = slider.value;

slider.oninput = function() {
  output.value = this.value;
}
window.onload = function ()
{
	load("style.css","css", function(){
	  load("microajax.js","js", function() {
	    setValues("/admin/generalvalues");
      setTimeout(warning1, 1000);
	    });
	});
}

function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

function warning1(){ 
  if (sfTmCB.checked){
    text.style.display = "block";
    text.innerHTML = "To change the values</br>disable the Safe Mode.";
    document.getElementById("devicename").disabled = true;
    document.getElementById("devicenumber").disabled = true;
    document.getElementById("baseTemp").disabled = true;
    document.getElementById("ds_resolution").disabled = true;
    document.getElementById("histG").disabled = true;
    document.getElementById("API").disabled = true;
    document.getElementById("histD").disabled = true;
    document.getElementById("cool").disabled = true;
    document.getElementById("sendTh").disabled = true;
    document.getElementById("hostServerName").disabled = true;
    document.getElementById("hostChannelNumber").disabled = true;
    document.getElementById("hostWriteKey").disabled = true;
    document.getElementById("hostUpdatePeriod").disabled = true;
    document.getElementById("zapisz").disabled = true;
  } 
}
</script>
)=====";

// Functions for this Page

void send_general_html()
{
	 if (config.enableSafetyTemp){
    server.send ( 200, "text/html", PAGE_AdminGeneralSettings ); 
    Serial.println(__FUNCTION__);
    return;
	 }
	if (server.args() > 0 )  // Save Settings
	{
		String temp = "";
    config.enableThingspeak = false;
    config.enableAPI = false;
    config.coolMode = false;
		for ( uint8_t i = 0; i < server.args(); i++ ) {
			if (server.argName(i) == "devicename") config.DeviceName = urldecode(server.arg(i)); 
      if (server.argName(i) == "devicenumber") config.DeviceNumber = server.arg(i).toInt();
      if (server.argName(i) == "baseTemp") config.baseTemp =  server.arg(i).toFloat();
      if (server.argName(i) == "ds_resolution") ds_resolution = server.arg(i).toInt();;      
      if (server.argName(i) == "hostServerName") config.hostServerName = urldecode(server.arg(i)); 
      if (server.argName(i) == "hostChannelNumber") config.hostChannelNumber =  server.arg(i).toInt();
      if (server.argName(i) == "hostWriteKey") config.hostWriteKey = urldecode(server.arg(i)); 
      if (server.argName(i) == "hostUpdatePeriod") config.hostUpdatePeriod =  server.arg(i).toInt();
      if (server.argName(i) == "API") config.enableAPI = true;
      if (server.argName(i) == "sendTh") config.enableThingspeak = true;
      if (server.argName(i) == "cool") config.coolMode = true;
      if (server.argName(i) == "histG") config.histeresisUpper =  server.arg(i).toFloat();
      if (server.argName(i) == "histD") config.histeresisLower =  server.arg(i).toFloat();            
		}
   if (ds_resolution != config.ds_resolution) {
    config.ds_resolution=ds_resolution;
    ds_resolution=1;
    resDS = resDsTranslate(); //function to translate DS resolution from number to text representation (for API)
   }
    updateTH = 1; // necessary for conversion of thingspeak data from String to char array 
  	WriteConfig();
	}
  
	 server.send ( 200, "text/html", PAGE_AdminGeneralSettings ); 
   Serial.println(__FUNCTION__);
}

void send_general_configuration_values_html()
{
	String values ="";
	values += "devicename|" +  (String)  config.DeviceName +  "|input\n";
  values += "devicenumber|" +  (String)  config.DeviceNumber +  "|input\n";
	values += "sf|" +   (String) (config.enableSafety ? "checked" : "") + "|chk\n";
  values += "sfTm|" +   (String) (config.enableSafetyTemp ? "checked" : "") + "|chk\n";
  values += "baseTemp|" +  (String) config.baseTemp +  "|input\n";
  values += "myRange|" +  (String) config.baseTemp +  "|input\n";
  values += "ds_resolution|" +  (String) config.ds_resolution +  "|input\n";
  values += "histG|" +  (String) config.histeresisUpper +  "|input\n";
  values += "histD|" +  (String) config.histeresisLower +  "|input\n";
  values += "cool|" +  (String) (config.coolMode ? "checked" : "") + "|chk\n";
  values += "hostServerName|" + (String) config.hostServerName +  "|input\n";
  values += "hostChannelNumber|" + (String) config.hostChannelNumber +  "|input\n";
  values += "hostWriteKey|" + (String) config.hostWriteKey +  "|input\n";
  values += "hostUpdatePeriod|" +  (String)  config.hostUpdatePeriod +  "|input\n";
  values += "API|" +  (String) (config.enableAPI ? "checked" : "") + "|chk\n";
  values += "sendTh|" +  (String) (config.enableThingspeak ? "checked" : "") + "|chk\n";
  server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__); 
}
