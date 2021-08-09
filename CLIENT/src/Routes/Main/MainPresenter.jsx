/* eslint-disable react/prop-types */
import React from 'react';
import styled, { css } from 'styled-components';
import Navigation from '../../Component/Navigation';
import LongButton from '../../Component/LongButton';
import BackButton from '../../Component/BackButton';

const Background = styled.div`
  padding-left: 32px;
  padding-top: 32px;
  padding-right: 32px;
  padding-bottom: 72px;

  height: 85vh;
  background: #f8f9fa;
`;

const MainWrap = styled.div`
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
`;
const Profile = styled.div`
  width: 120px;
  height: 120px;
  border-radius: 50%;
  background-color: black;
`;
const NameText = styled.div`
  text-align: center;
  font-size: 32px;
  margin: 4px;
  ${(props) =>
    props.small &&
    css`
      font-size: 16px;
      margin-bottom: 16px;
    `}
`;

function MainPresenter({ history }) {
  return (
    <>
      <Background>
        <BackButton history={history} />
        <MainWrap>
          <Profile />
          <NameText>KimUndong</NameText>
          <NameText small>Deagu ,Korea ,KMU PARK</NameText>
          <LongButton color="black"> EDIT PROFILE </LongButton>
          <LongButton> MAP </LongButton>
        </MainWrap>
        <Navigation />
      </Background>
    </>
  );
}

export default MainPresenter;
