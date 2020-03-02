//
//  HTML PAGE
//
const char PAGE_AdminMainPage[] PROGMEM = R"=====(
<title>TERMIKUS</title>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1" />
<div class="tiCen">TERMIKUS</div>
<hr>
<a href="config.html" class="btn btn--m btn--blue btn--full">WiFi Configuration</a>
<a href="ntp.html" class="btn btn--m btn--blue btn--full">NTP Settings</a>
<a href="info.html" class="btn btn--m btn--blue btn--full">Network Review</a><hr>
<a href="general.html" class="btn btn--m btn--blue btn--full">Basic Settings</a>
<a href="safemode.html" class="btn btn--m btn--blue btn--full">Safe Mode</a><hr>
<a href="program1.html" class="btn btn--m btn--blue btn--full">Programs</a>
<a href="intervals.html" class="btn btn--m btn--blue btn--full">Interval Control</a><hr>
<a href="termikus.html" class="btn btn--m btn--blue btn--full">Parameters Review</a>
<hr>

<script>
window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        // Do something after load...
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

</script>
)=====";
