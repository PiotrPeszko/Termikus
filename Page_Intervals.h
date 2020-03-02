//
//  HTML PAGE
//

const char PAGE_Intervals[] PROGMEM =  R"=====(
<title>TERMIKUS</title>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1" />
<body>
<div class="tiCen">
<a href="admin.html" class="btn btn--m btn--blue">&uarr;</a>&nbsp;&nbsp;<strong>Interval Control</strong></div>
<form action="" method="post">
<table class="cent">
<tr><td align="left" colspan="2"><hr></td></tr>
<tr><td colspan="2"><input type="checkbox" id="sfTm" name="sfTm"><input type="checkbox" id="mMode" name="mMode"><span id="warning" name="warning">&nbsp;</span></td></tr>
<tr><td align="right">Temperature :</td><td><input type="text" id="tManual" name="tManual" size="4" value="21"></td></tr>
<tr><td align="left" colspan="2"><br></td></tr>
<tr><td class="slidecontainer" colspan=2><input type="range" min="0" max="35" value="" step="0.5" class="slider" id="myRange"></td></tr>
<tr><td align="left" colspan="2"><br></td></tr>
<tr><td align="right">Duration :</td><td>
<select id="duration" name="duration" class="oth">
<option value="0">00:00</option>
<option value="15">00:15</option>
<option value="30">00:30</option>
<option value="45">00:45</option>
<option value="60">01:00</option>
<option value="90">01:30</option>
<option value="120">02:00</option>
<option value="150">02:30</option>
<option value="180">03:00</option>
<option value="210">03:30</option>
<option value="240">04:00</option>
<option value="270">04:30</option>
<option value="300">05:00</option>
<option value="330">05:30</option>
<option value="360">06:00</option>
<option value="420">07:00</option>
<option value="480">08:00</option>
<option value="540">09:00</option>
<option value="600">10:00</option>
<option value="660">11:00</option>
<option value="720">12:00</option>
<option value="1440">24:00</option>
</select> hh:mm</td></tr>
<tr><td align="right">Remaining time:</td><td id="timeToGo"></td></tr>
<tr><td align="left" colspan="2"><hr></td></tr>
</table>
<table class="cent">
<tr><td align="center"><input type="submit" style="width:150px" id="guzik" name="guzik" class="btn btn--l btn--blue" value="Save"></td></tr>
</table>
</form>
<p class="info">To clear the timer: set time to 00:00 and SAVE.</br></br>To change the time of the running timer, first clear the timer.<br></p>
<script>
var  sfTmCB = document.getElementById('sfTm');
var text = document.getElementById('warning');
var manMode  = document.getElementById('mMode');
var slider = document.getElementById("myRange");
var output = document.getElementById("tManual");
slider.value = output.value;
slider.oninput = function() {
  output.value = this.value;
}

window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/intervals");
    setTimeout(warning1, 1000);
    });
  });
}

function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

function warning1(){ 
   if (sfTmCB.checked){
    text.style.display = "block";
    text.innerHTML = "To change timer values</br>disable the Safe Mode.";
    document.getElementById("guzik").disabled = true;
   } else if (mMode.checked){
    text.style.display = "block";
    text.style.backgroundColor = "green";
    text.innerHTML = "Timer is running!";
    text.style.height = "1.5em";
  }
}
</script>
)=====";


void send_intervals_values()
{
   if (config.enableSafetyTemp){
    server.send ( 200, "text/html", PAGE_Intervals ); 
    Serial.println(__FUNCTION__);
    return;
   }
  if (server.args() > 0 )  {// Save Settings
   for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "tManual") intervalTemperature = server.arg(i).toFloat();
      if (server.argName(i) == "duration") intervalDuration = server.arg(i).toInt();
    }
  }
  server.send ( 200, "text/html", PAGE_Intervals); 
  Serial.println(__FUNCTION__);
}

void send_intervals_values_html()
{
  unsigned int timeToGo = timeToGoConv();
  
  String values ="";
  values += "sfTm|" +   (String) (config.enableSafetyTemp ? "checked" : "") + "|chk\n";
  values += "mMode|" +   (String) (intervalMode ? "checked" : "") + "|chk\n";
  values += "tManual|" +  (String)  intervalTemperature +  "|input\n";
  values += "myRange|" +  (String)  intervalTemperature +  "|input\n";
  values += "duration|" +   (String)  intervalDuration +  "|input\n";
  values += "timeToGo|" +   (String)  timeToGo +  " min." +"|div\n";
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__); 
}
