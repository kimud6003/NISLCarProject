import React from 'react';
import { BrowserRouter, Switch, Route } from 'react-router-dom';
import icon from '../assets/icon.svg';
import './App.global.css';
import { UserProvider } from './context/User.context';
import InitPresenter from './Routes/Init/InitPresenter';
import LoginPresenter from './Routes/Login/LoginPresenter';

export default function App() {
  return (
    <UserProvider>
      <BrowserRouter>
        <Switch>
          <Route path="/Login" component={InitPresenter} />
          <Route path="/" component={LoginPresenter} />
        </Switch>
      </BrowserRouter>
    </UserProvider>
  );
}
