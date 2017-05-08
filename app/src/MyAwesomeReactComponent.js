import React from 'react';
import RaisedButton from 'material-ui/RaisedButton';

const MyAwesomeReactComponent = (props) => (
  <RaisedButton label="Toggle led" onTouchTap={(e)=>{
    props.client.publish("led/status", "1")
  }}/>
);

export default MyAwesomeReactComponent;
