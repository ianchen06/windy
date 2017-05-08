import injectTapEventPlugin from 'react-tap-event-plugin';
import mqtt from 'mqtt';
import React from 'react';
import ReactDOM from 'react-dom';

import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider';
import MyAwesomeReactComponent from './MyAwesomeReactComponent';
import AppBar from 'material-ui/AppBar';
import Slider from 'material-ui/Slider';

import css from './static/css/index.css';


// Needed for onTouchTap
// http://stackoverflow.com/a/34015469/988941
injectTapEventPlugin();


const client = mqtt.connect()
client.subscribe(['fan/speed', 'led/status', 'mqtt/demo'])

client.on("message", function (topic, payload) {
  alert([topic, payload].join(": "))
  //client.end()
})

client.publish("mqtt/demo", "hello world!")

const App = () => (
  <MuiThemeProvider>
    <div>
      <AppBar title="Windy" iconClassNameRight="muidocs-icon-navigation-expand-more" />
      <MyAwesomeReactComponent client={client}/>
      <h1>Current fan speed</h1>
      <Slider onChange={(e, val)=>{
        e.preventDefault()
        console.log("value is ", val)
      }}/>
    </div>
  </MuiThemeProvider>
);

ReactDOM.render(
  <App />,
  document.getElementById('root')
);
