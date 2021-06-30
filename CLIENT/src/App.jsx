import React from 'react';
import { BrowserRouter as Router, Switch, Route } from 'react-router-dom';
import icon from '../assets/icon.svg';
import './App.global.css';
import {UserProvider} from './context/User.context'
import Sider from './components/main';

const Hello = () => {
  return (
    <div>
      <UserProvider>
        <Sider/>
      </UserProvider>
    </div>
  );
};

export default function App() {
  return (
    <Router>
      <Switch>
        <Route path="/" component={Hello} />
      </Switch>
    </Router>
  );
}

