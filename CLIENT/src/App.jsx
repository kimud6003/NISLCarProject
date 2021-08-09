import React from 'react';
import { HashRouter, Switch, Route } from 'react-router-dom';
import './App.global.css';
import { UserProvider } from './context/User.context';
import InitPresenter from './Routes/Init/InitPresenter';
import LoginPresenter from './Routes/Login/LoginPresenter';
import MainPresenter from './Routes/Main/MainPresenter';
import ChatPresenter from './Routes/Chat/ChatPresenter';

export default function App() {
  return (
    <UserProvider>
      <HashRouter>
        <Switch>
          <Route path="/" exact component={InitPresenter} />
          <Route path="/Login" exact component={LoginPresenter} />
          <Route path="/Main" exact component={MainPresenter} />
          <Route path="/Chat" exact component={ChatPresenter} />
        </Switch>
      </HashRouter>
    </UserProvider>
  );
}
