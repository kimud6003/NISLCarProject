import React from 'react';
import { BrowserRouter as Router, Switch, Route } from 'react-router-dom';
import icon from '../assets/icon.svg';
import './App.global.css';
import styled,{ createGlobalStyle } from 'styled-components';
import {UserProvider} from './context/User.context';
import LoginPresenter from './Routes/Login/LoginPresenter';



export default function App() {
  return (
    <UserProvider>
    <Router>
      <Switch>
        <Route path="/" component={LoginPresenter} />
      </Switch>
    </Router>
    </UserProvider>
  );
}

