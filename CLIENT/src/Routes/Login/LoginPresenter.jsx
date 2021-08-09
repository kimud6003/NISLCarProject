/* eslint-disable react/prop-types */
import React from 'react';
import { AiOutlineLeft } from 'react-icons/ai';
import { Link } from 'react-router-dom';
import styled from 'styled-components';

const Background = styled.div`
  padding-left: 16px;
  padding-top: 32px;
  padding-right: 32px;
  padding-bottom: 72px;

  height: 85vh;
  background: #f8f9fa;
`;
const InsertForm = styled.form``;

const Input = styled.input`
  padding: 12px;
  margin: 12px;
  border-radius: 4px;
  border: 1px solid #dee2e6;
  width: 100%;
  outline: none;
  font-size: 18px;
  box-sizing: border-box;
`;
const LongButton = styled.button`
  padding: 12px;
  margin: 12px;
  border-radius: 4px;
  border: 1px solid black;
  background-color: black;
  width: 100%;
  outline: none;
  font-size: 18px;
  box-sizing: border-box;
  color: white;
`;
const BackButton = styled.button`
  border: 0;
  outline: 0;
  background: #f8f9fa;
`;

function LoginPresenter({ history }) {
  const goBack = () => {
    history.goBack();
  };
  return (
    <>
      <Background>
        <BackButton>
          <AiOutlineLeft onClick={goBack} />
        </BackButton>
        <InsertForm>
          <Input placeholder="Car number" />
          <Input placeholder="Phone number" />
          <Input placeholder="Phone number auth" />
        </InsertForm>
        <Link to="/main">
          <LongButton>Next</LongButton>
        </Link>
        <LongButton>Cancel</LongButton>
      </Background>
    </>
  );
}

export default LoginPresenter;
