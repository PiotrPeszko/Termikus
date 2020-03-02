//
//  HTML PAGE
//
const char PAGE_Termikus[] PROGMEM = R"=====(
<title>TERMIKUS</title>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1" />
<body>
  <div class="tiCen"><a href="admin.html" class="btn btn--m btn--blue">&uarr;</a>&nbsp;&nbsp;<strong>Basic Parameters</strong></div>
  <hr>
<table class="cent">
<tr><td>Device name:</td><td id="devicename"></td></tr>
<tr><td>Device number:</td><td id="devicenumber"></td></tr>
<tr><td colspan="2"><hr></td></tr>
<tr><td>Safe mode:</td><td id="safety"></td></tr>
<tr><td>Main temperature:</td><td id="baseTemp"></td></tr>
<tr><td>Measured temperature:</td><td id="temperatura"></td></tr>
<tr><td>Active program:</td><td id="progFit"></td></tr>
<tr><td>Program temperature:</td><td id="setTemp"></td></tr>
<tr><td>Relay status:</td><td id="relay"></td></tr>
<tr><td colspan="2"><hr></td></tr>
<tr><td>Upper histeresis:</td><td id="histeresisUpper"></td></tr>
<tr><td>Lower histeresis:</td><td id="histeresisLower"></td></tr>
<tr><td>DS18B20 resolution:</td><td id="ds_resolution"></td></tr>
<tr><td>Cooling mode:</td><td id="cool"></td></tr>
<tr><td>Thingspeak update:</td><td id="thStatus"></td></tr>
<tr><td>Free stack:</td><td id="stos"></td></tr>
<tr><td colspan="2"><hr></td></tr>
<tr><td colspan="2" align="center">v 1.11e</br>www.termikus.pl</br>&copy;2020 Piotr Peszko</td></tr>
</table>

<script>                
		window.onload = function ()
		{
			load("style.css","css", function() 
			{
				load("microajax.js","js", function() 
				{
						setValues("/admin/filldynamicdata");  //-- this function calls the function on the ESP      
				});
			});
		}
		function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
</body>
</html>
)=====";


void filldynamicdata()
{   
    String thStatus;
    if (channelUpdateStatus == 200)
    {
      thStatus = "Success";
    } else {
      thStatus = String(channelUpdateStatus);
    }

    String relStatus;
    if (relayStatus == 1)
    {
      relStatus = "ON";
    } else {
      relStatus = "OFF";
    }

    String program;
    if(programFit==0)
    {
      program = "MAIN";
    }else if (programFit==10){
      program = "INTERVAL";
    } else {
      program = programFit;
    }
    
    long stos = ESP.getFreeHeap();
    String values ="";  // Build a string, like this:  ID|VALUE|TYPE
    values += "devicename|" + (String)config.DeviceName + "|div\n";
    values += "devicenumber|" + (String)config.DeviceNumber + "|div\n";
    values += "safety|" + (String)config.enableSafety + (String)config.enableSafetyTemp + "|div\n";
    values += "baseTemp|" +  (String)config.baseTemp + "|div\n";
    values += "temperatura|" + (String)measureTemp + "|div\n";
    values += "progFit|" + (String)program + "|div\n";
    values += "setTemp|" + (String) setTemp + "|div\n";
    values += "relay|" + (String)relStatus + "|div\n";
    values += "histeresisUpper|" + (String) config.histeresisUpper + "|div\n";  
    values += "histeresisLower|" + (String) config.histeresisLower + "|div\n";  
    values += "ds_resolution|" + (String) resDS + "&deg;C" + "|div\n";  
    values += "cool|" +  (String) config.coolMode + "|div\n";
    values += "thStatus|" + (String) thStatus +"|div\n";
    values += "stos|" + (String) stos +"|div\n"; 
    server.send ( 200, "text/plain", values);
    
}
