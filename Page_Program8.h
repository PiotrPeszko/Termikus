const char PAGE_Program8[] PROGMEM =  R"=====(

<title>TERMIKUS</title>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1" />
</head>
<body>
<div class="tiCen">
<a href="admin.html" class="btn btn--m btn--blue">&uarr;</a>
<a href="program1.html"  class="btn btn--m btn--blue">1</a><a href="program2.html"  class="btn btn--m btn--blue">2</a><a href="program3.html"  class="btn btn--m btn--blue">3</a><a href="program4.html"  class="btn btn--m btn--blue">4</a><a href="program5.html"  class="btn btn--m btn--blue">5</a><a href="program6.html"  class="btn btn--m btn--blue">6</a><a href="program7.html"  class="btn btn--m btn--blue">7</a><a href="#" class="btn btn--m act">8</a>
</div>
<hr>
<form action="" method="post">
<table class="cent">
<tr><td align="right">Enable:</td><td><label class="switch"><input type="checkbox" id="PrEnabled" name="PrEnabled"><span class="sliderBox"></span></label></td></tr>
<tr><td colspan="2"><input type="checkbox" id="sfTm" name="sfTm"><input type="checkbox" id="sf" name="sf"><p id="warning">&nbsp;</p></td></tr>
<tr><td align="right">Temperature:</td><td><input type="text" id="tProgramu" name="tProgramu" size="2" class="temp"></tr>
<tr><td align="left" colspan="2"><br></td></tr>
<tr><td class="slidecontainer" colspan=3><input type="range" min="0" max="35" value="21" step="0.5" class="slider" id="myRange"></td></tr>
<tr><td align="left" colspan="2"><br></td></tr>
<tr><td align="right">Start time:</td><td>
<select  id="tonhour" name="tonhour"><option value="0">00</option><option value="1">01</option><option value="2">02</option><option value="3">03</option><option value="4">04</option><option value="5">05</option><option value="6">06</option><option value="7">07</option><option value="8">08</option><option value="9">09</option><option value="10">10</option><option value="11">11</option><option value="12">12</option><option value="13">13</option><option value="14">14</option><option value="15">15</option><option value="16">16</option><option value="17">17</option><option value="18">18</option><option value="19">19</option><option value="20">20</option><option value="21">21</option> <option value="22">22</option><option value="23">23</option></select>
:
<select id="tonminute" name="tonminute"><option value="0">00</option><option value="1">01</option><option value="2">02</option><option value="3">03</option><option value="4">04</option><option value="5">05</option>
  <option value="6">06</option><option value="7">07</option><option value="8">08</option><option value="9">09</option><option value="10">10</option><option value="11">11</option><option value="12">12</option>
  <option value="13">13</option><option value="14">14</option><option value="15">15</option><option value="16">16</option><option value="17">17</option><option value="18">18</option><option value="19">19</option>
  <option value="20">20</option><option value="21">21</option><option value="22">22</option><option value="23">23</option><option value="24">24</option><option value="25">25</option><option value="26">26</option>
  <option value="27">27</option><option value="28">28</option><option value="29">29</option><option value="30">30</option><option value="31">31</option><option value="32">32</option><option value="33">33</option>
  <option value="34">34</option><option value="35">35</option><option value="36">36</option><option value="37">37</option><option value="38">38</option><option value="39">39</option><option value="40">40</option>
  <option value="41">41</option><option value="42">42</option><option value="43">43</option><option value="44">44</option><option value="45">45</option><option value="46">46</option><option value="47">47</option>
  <option value="48">48</option><option value="49">49</option><option value="50">50</option><option value="51">51</option><option value="52">52</option><option value="53">53</option><option value="54">54</option>
  <option value="55">55</option><option value="56">56</option><option value="57">57</option><option value="58">58</option><option value="59">59</option></td></tr>
<tr>
   <td align="right">Stop time:</td>
  <td><select  id="toffhour" name="toffhour">
  <option value="0">00</option><option value="1">01</option><option value="2">02</option><option value="3">03</option><option value="4">04</option><option value="5">05</option><option value="6">06</option><option value="7">07</option><option value="8">08</option><option value="9">09</option><option value="10">10</option><option value="11">11</option><option value="12">12</option><option value="13">13</option><option value="14">14</option><option value="15">15</option><option value="16">16</option><option value="17">17</option><option value="18">18</option><option value="19">19</option><option value="20">20</option><option value="21">21</option><option value="22">22</option><option value="23">23</option></select>
  :
  <select id="toffminute" name="toffminute">
  <option value="0">00</option><option value="1">01</option><option value="2">02</option><option value="3">03</option><option value="4">04</option><option value="5">05</option><option value="6">06</option>
  <option value="7">07</option><option value="8">08</option><option value="9">09</option><option value="10">10</option><option value="11">11</option><option value="12">12</option><option value="13">13</option>
  <option value="14">14</option><option value="15">15</option><option value="16">16</option><option value="17">17</option><option value="18">18</option><option value="19">19</option><option value="20">20</option>
  <option value="21">21</option><option value="22">22</option><option value="23">23</option><option value="24">24</option><option value="25">25</option><option value="26">26</option><option value="27">27</option>
  <option value="28">28</option><option value="29">29</option><option value="30">30</option><option value="31">31</option><option value="32">32</option><option value="33">33</option><option value="34">34</option>
  <option value="35">35</option><option value="36">36</option><option value="37">37</option><option value="38">38</option><option value="39">39</option><option value="40">40</option><option value="41">41</option>
  <option value="42">42</option><option value="43">43</option><option value="44">44</option><option value="45">45</option><option value="46">46</option><option value="47">47</option><option value="48">48</option>
  <option value="49">49</option><option value="50">50</option><option value="51">51</option><option value="52">52</option><option value="53">53</option><option value="54">54</option><option value="55">55</option>
  <option value="56">56</option><option value="57">57</option><option value="58">58</option><option value="59">59</option></td>
</tr>
<tr>
  <td align="left" colspan="3"><hr></td>
</tr>
</table>
<table class="cent">
<tr><td>Mo</td><td>Tu</td><td>We</td><td>Th</td><td>Fr</td><td>Sa</td><td>Su</td></tr>
<tr>
<td><label class="container"><input type="checkbox" id="pnCheckbox" name="pnCheckbox"><span class="checkmark"></span></label></td>
<td><label class="container"><input type="checkbox" id="wtCheckbox" name="wtCheckbox"><span class="checkmark"></span></label></td>
<td><label class="container"><input type="checkbox" id="srCheckbox" name="srCheckbox"><span class="checkmark"></span></label></td>
<td><label class="container"><input type="checkbox" id="czCheckbox" name="czCheckbox"><span class="checkmark"></span></label></td>
<td><label class="container"><input type="checkbox" id="ptCheckbox" name="ptCheckbox"><span class="checkmark"></span></label></td>
<td><label class="container"><input type="checkbox" id="soCheckbox" name="soCheckbox"><span class="checkmark"></span></label></td>
<td><label class="container"><input type="checkbox" id="ndCheckbox" name="ndCheckbox"><span class="checkmark"></span></label></td>
</tr>
</table>
</br></br>
<table class="cent">
<tr>
<td><a href="program7.html" class="btn btn--l btn--blue">&larr;</a></td>
<td align="center"><input type="submit" style="width:150px" class="btn btn--l btn--blue" value="Save"></td>
<td align="right"><a href="program1.html" class="btn btn--l btn--blue">&rarr;</a></td>
</tr>
</table>
</form>

<script>
var text = document.getElementById('warning');
var  sfTmCB = document.getElementById('sfTm');
var  sfCB = document.getElementById('sf');
var slider = document.getElementById("myRange");
var output = document.getElementById("tProgramu");
output.value = slider.value;

slider.oninput = function() {
  output.value = this.value;
}

window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/program_values8"); 
        setTimeout(warning1, 1000);
    });
  });
}

function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
function warning1(){ 
  if (!sfCB.checked && sfTmCB.checked){
    text.style.display = "block";
    text.innerHTML = "Push the button to</br>disable the Safe Mode!";
  } else if (sfCB.checked && sfTmCB.checked){
    text.style.display = "block";
    text.style.backgroundColor = "green";
    text.innerHTML = "Push the button after the save to confirm changes.";
  }
}
</script>

)=====";


// Functions for this Page

/**
  progData[x].Enabled=bitRead(weekdays,0);
  progData[x].Pn=bitRead(weekdays,1);
  progData[x].Wt=bitRead(weekdays,2);
  progData[x].Sr=bitRead(weekdays,3);
  progData[x].Cz=bitRead(weekdays,4);
  progData[x].Pt=bitRead(weekdays,5);
  progData[x].So=bitRead(weekdays,6);
  progData[x].Nd=bitRead(weekdays,7);
**/

void save_program8_values()
{
  if (server.args() > 0 )  // Save Settings
  {
    whichMemoryBank(8);
    progData[memoryBank].Enabled = false;
    progData[memoryBank].Pn = false;
    progData[memoryBank].Wt = false;
    progData[memoryBank].Sr = false;
    progData[memoryBank].Cz = false;
    progData[memoryBank].Pt = false;
    progData[memoryBank].So = false;
    progData[memoryBank].Nd = false;
    //String temp = "";
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "PrEnabled") progData[memoryBank].Enabled = true; 
      if (server.argName(i) == "tonhour") progData[memoryBank].startH =  server.arg(i).toInt(); 
      if (server.argName(i) == "tonminute") progData[memoryBank].startM =  server.arg(i).toInt(); 
      if (server.argName(i) == "toffhour") progData[memoryBank].stopH =  server.arg(i).toInt(); 
      if (server.argName(i) == "toffminute") progData[memoryBank].stopM =  server.arg(i).toInt(); 
      if (server.argName(i) == "tProgramu") progData[memoryBank].tempProgramu =  server.arg(i).toFloat();
      if (server.argName(i) == "pnCheckbox") progData[memoryBank].Pn = true;
      if (server.argName(i) == "wtCheckbox") progData[memoryBank].Wt = true; 
      if (server.argName(i) == "srCheckbox") progData[memoryBank].Sr = true; 
      if (server.argName(i) == "czCheckbox") progData[memoryBank].Cz = true; 
      if (server.argName(i) == "ptCheckbox") progData[memoryBank].Pt = true; 
      if (server.argName(i) == "soCheckbox") progData[memoryBank].So = true; 
      if (server.argName(i) == "ndCheckbox") progData[memoryBank].Nd = true; 
    }
    midnightCheck(memoryBank); // end time change to 23:59 if 00:00 set for end time    
    writeProgram(memoryBank); //funkcja zapisująca do EEPROM...
  //  SafeModeTimeOutCounter = 0;
  }
  server.send ( 200, "text/html", PAGE_Program8 ); // ... i wyświetlająca
  Serial.println(__FUNCTION__);
}

void send_programator_values8_html()
{
  whichMemoryBank(8);
  String values ="";
  values += "tonhour|" +   (String) progData[memoryBank].startH +  "|input\n";
  values += "tonminute|" +  (String)  progData[memoryBank].startM +  "|input\n";
  values += "toffhour|" +   (String)  progData[memoryBank].stopH +  "|input\n";
  values += "toffminute|" +   (String)  progData[memoryBank].stopM +  "|input\n";
  values += "tProgramu|" +   (String)  progData[memoryBank].tempProgramu +  "|input\n";
  values += "myRange|" +  (String)  progData[memoryBank].tempProgramu +  "|input\n";
  values += "PrEnabled|" +  (String) (progData[memoryBank].Enabled ? "checked" : "") + "|chk\n";
  values += "pnCheckbox|" +  (String) (progData[memoryBank].Pn ? "checked" : "") + "|chk\n";
  values += "wtCheckbox|" +  (String) (progData[memoryBank].Wt ? "checked" : "") + "|chk\n";
  values += "srCheckbox|" +  (String) (progData[memoryBank].Sr ? "checked" : "") + "|chk\n";
  values += "czCheckbox|" +  (String) (progData[memoryBank].Cz ? "checked" : "") + "|chk\n";
  values += "ptCheckbox|" +  (String) (progData[memoryBank].Pt ? "checked" : "") + "|chk\n";
  values += "soCheckbox|" +  (String) (progData[memoryBank].So ? "checked" : "") + "|chk\n";
  values += "ndCheckbox|" +  (String) (progData[memoryBank].Nd ? "checked" : "") + "|chk\n";
  values += "sf|" +   (String) (config.enableSafety ? "checked" : "") + "|chk\n";
  values += "sfTm|" +   (String) (config.enableSafetyTemp ? "checked" : "") + "|chk\n";
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__); 
}
