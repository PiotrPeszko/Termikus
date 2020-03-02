//
//  HTML PAGE
//
const char PAGE_SafeModeSettings[] PROGMEM =  R"=====(
<title>TERMIKUS</title>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1" />
<div class="tiCen"><a href="admin.html"  class="btn btn--m btn--blue">&uarr;</a>&nbsp;&nbsp;<strong>Safe Mode:</strong></div>
<form action="" method="get">
<hr>
<table class="cent">
<tr><td align="center">Enable:</td><td><label class="switch"><input type="checkbox" id="safety" name="safety" onclick="myFunction()"><span class="sliderBox"></span></label></td></tr>
<tr><td colspan="2"><input type="checkbox" id="sfTm" name="sfTm"><p id="warning">&nbsp;</p></td></tr>
<tr><td colspan="2">&nbsp;</td></tr>
<tr><td colspan="2"><hr></td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save" id="zapisz"></td></tr>
</table>
</form>
<p class="info">When safe mode is <b>enabled</b>:</br>
- Changing network and thermostat configuration is not possible.</br>
- Program changes are possible, but require confirmative button press.</br></br>
When safe mode is <b>disabled</b>:</br>
- All configuration modifications are allowed. No button press is required.</br>
</p>
<script>
var text = document.getElementById('warning');
var  sfTmCB = document.getElementById('sfTm');
var  sfCB = document.getElementById('safety');

window.onload = function ()
{
	load("style.css","css", function(){
	  load("microajax.js","js", function() {
	    setValues("/admin/safemodevalues");
      setTimeout(warning1, 1000);
	    });
	});
}

function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

function myFunction() {
 var statusCB = sfTmCB.checked;
  if (!sfCB.checked && sfTmCB.checked){
    text.style.display = "block";
    text.innerHTML = "Teraz zapisz zmiany.";
  } else {
     text.style.display = "none";
  }
}
function warning1(){ 
  if (!sfCB.checked && sfTmCB.checked){
    text.style.display = "block";
    text.innerHTML = "Teraz potwierdź zmianę przyciskiem na termostatcie i przeładuj stronę.";
  } 
}
</script>
)=====";


// Functions for this Page

void send_safemode_html()
{
	if (server.args() > 0 )  // Save Settings
	{
    config.enableSafety = false;
		for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "safety") {
        config.enableSafety = true;
        config.enableSafetyTemp = true;
  //      SafeModeTimeOutCounter = SafeModeTimeOut;
      }
		}
		WriteConfig();
	}
	server.send ( 200, "text/html", PAGE_SafeModeSettings); 
	Serial.println(__FUNCTION__);
}

void send_safemode_values_html()
{
	String values ="";
	values += "safety|" +   (String) (config.enableSafety ? "checked" : "") + "|chk\n";
  values += "sfTm|" +   (String) (config.enableSafetyTemp ? "checked" : "") + "|chk\n";
  server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__); 
}
