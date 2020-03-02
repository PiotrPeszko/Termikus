const char PAGE_Style_css[] PROGMEM = R"=====(
body {background-color:#7A98BF; color: #000; font-family: avenir, helvetica, arial, sans-serif; letter-spacing: 0.08em; margin: 10px 0px;} 
hr {border: 1px solid #A3BFD9; width:340px;}
p {width:350px;letter-spacing:0.1em; padding:0.75em 0.75em;text-decoration:none;border-radius:0.3em;}
.info {margin-left:auto;margin-right:auto;background-color:#D5E5F2;width:310px}
.btn, .btn:link, .btn:visited {border-radius: 0.3em;border-style: solid;border-width: 1px;border-color: #7A98BF;color: #fff;display: inline-block;font-family: avenir, helvetica, arial, sans-serif;letter-spacing: 0.15em; margin-bottom: 0.5em;padding: 1em 0.75em;text-decoration: none;text-transform: uppercase;-webkit-transition: color 0.4s, background-color 0.4s, border 0.4s;transition: color 0.4s, background-color 0.4s, border 0.4s;}
.btn:hover, .btn:focus{
  color: #7FDBFF;
  border: 1px solid #193559;
  -webkit-transition: background-color 0.3s, color 0.3s, border 0.3s;
  transition: background-color 0.3s, color 0.3s, border 0.3s;
}
.btn:active{
  color: #0074D9;
  border: 1px solid #0074D9;
  -webkit-transition: background-color 0.3s, color 0.3s, border 0.3s;
  transition: background-color 0.3s, color 0.3s, border 0.3s;
}
.btn--s
  {
    font-size: 12px;
  }
.btn--m{
    font-size: 14px;
  margin-right:2px;
  }
.btn--l{
    font-size: 18px; border-radius: 0.25em !important;
  border-color: #193559;
  }
.btn--full, .btn--full:link{
  border-radius: 0.4em;
  display: block;
  margin-left: auto;
  margin-right: auto;
  text-align: center;
  width: 80%;
  }
.btn--blue:link, .btn--blue:visited{
  color: #fff;
  background-color: #3C6AA6;
  }
.btn--blue:hover, .btn--blue:focus{
  color: #fff !important;
  background-color: #193559;
}
.btn--blue:active{
  color: #0074D9;
  background-color: #001F3F; border-color: #001F3F;
}
.act{background-color: #193559;}
.tiCen{border-radius: 0.25em;font-weight:bold;display: block;margin-left: auto;margin-right: auto;text-align: center;width: 100%;}  

select {background-color: #ccc; font-size: 1.1em;} 
input {background-color: #ccc;font-size: 1.1em; border: 1px solid #ccc;border-radius: 4px;box-sizing: border-box;}
input.temp {font-size: 1.5em;}
input[type=submit]{color: white; background-color: #3C6AA6; border-color: #3C6AA6}

@media screen and (min-width: 27em) {
  .btn--full {
  max-width: 22em !important;}
}
slidecontainer{
 width: 100%;
}
.slider {
  -webkit-appearance: none;
   width: 100%;
   height: 10px;
   border-radius: 5px;
   background: #193559;
   outline: none;
   opacity: 0.7;
   -webkit-transition: .2s;
  transition: opacity .2s;
}
.slider:hover {
  opacity: 1;
}
.slider::-webkit-slider-thumb{
 -webkit-appearance: none;
 appearance: none;
 width: 25px;
 height: 25px;
 border-radius: 50%;
 background: #ff0000;
 cursor: pointer;
}
.slider::-moz-range-thumb{
 width: 25px;
 height: 25px;
 border-radius: 50%;
 background: #ff0000;
 cursor: pointer;
}
#sfTm, #sf, #mMode, #warning{
  display:none;
}
#warning, #safemode{text-align:center;background-color:red;color:white;padding: 5px 0 5px 0;border-radius:0.3em;}

table.cent{width:350px; margin-left:auto; margin-right:auto; border:0px;}
.switch {position: relative;display: inline-block;width: 60px;height: 34px;}
.switch input {opacity: 0;width: 0;height: 0;}
.sliderBox {position: absolute;cursor: pointer;top: 0;left: 0;right: 0;bottom: 0;border-radius: 5px;background-color: #ccc;
-webkit-transition: .4s;
transition: .4s;
}

.sliderBox:before {
  position: absolute;
  content: "";
  height: 26px;
  width: 26px;
  left: 4px;
  bottom: 4px;
  border-radius: 10%;
  background-color: white;
  -webkit-transition: .4s;
  transition: .4s;
}

input:checked + .sliderBox {
  background-color: #193559;
}

input:focus + .sliderBox {
  box-shadow: 0 0 1px #2196F3;
}

input:checked + .sliderBox:before {
  -webkit-transform: translateX(26px);
  -ms-transform: translateX(26x);
  transform: translateX(26px);
}
/* The container */
.container {
  display: block;
  position: relative;
  padding-left: 35px;
  margin-bottom: 12px;
  cursor: pointer;
  font-size: 22px;
  -webkit-user-select: none;
  -moz-user-select: none;
  -ms-user-select: none;
  user-select: none;
}
.container input {
  position: absolute;
  opacity: 0;
  cursor: pointer;
  height: 0;
  width: 0;
}
.checkmark {
  position: absolute;
  top: 0;
  left: 0;
  height: 25px;
  width: 25px;
  background-color: #eee;
}
.container:hover input ~ .checkmark {
  background-color: #ccc;
}
.container input:checked ~ .checkmark {
  background-color: #193559;
}
.checkmark:after {
  content: "";
  position: absolute;
  display: none;
}
.container input:checked ~ .checkmark:after {
  display: block;
}
.container .checkmark:after {
  left: 9px;
  top: 5px;
  width: 5px;
  height: 10px;
  border: solid white;
  border-width: 0 3px 3px 0;
  -webkit-transform: rotate(45deg);
  -ms-transform: rotate(45deg);
  transform: rotate(45deg);
}

)=====";
