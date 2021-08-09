/* eslint-disable react/prop-types */
import React from 'react';
import {
  AiOutlineMessage,
  AiFillPlusCircle,
  AiOutlineUser,
} from 'react-icons/ai';
import { Link } from 'react-router-dom';
import styled, { css } from 'styled-components';

const ImageButton = styled(Link)`
  color: black;
  position: relative;
  border: 0;
  outline: 0;
  background: #f8f9fa;
  left: 0px;
  font-size: 32px;
  font-weight: lighter;
  margin: 16px;
`;

const NavigationBar = styled.div`
  position: fixed;
  bottom: 0;
  left: 0;
  height: 70px;
  width: 100%;
  border-top: 1px solid #b3b3b3;
  display: flex;
  justify-content: space-between;
`;

function Navigation() {
  return (
    <>
      <NavigationBar>
        <ImageButton to="/chat">
          <AiOutlineMessage />
        </ImageButton>
        <ImageButton to="/chat">
          <AiFillPlusCircle />
        </ImageButton>
        <ImageButton to="/chat">
          <AiOutlineUser />
        </ImageButton>
      </NavigationBar>
    </>
  );
}

export default Navigation;
