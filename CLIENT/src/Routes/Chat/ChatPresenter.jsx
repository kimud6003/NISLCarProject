/* eslint-disable react/prop-types */
import React from 'react';
import styled from 'styled-components';
import Navigation from '../../Component/Navigation';
import BackButton from '../../Component/BackButton';

const Background = styled.div`
  padding-left: 32px;
  padding-top: 32px;
  padding-right: 32px;
  padding-bottom: 72px;

  height: 85vh;
  background: #f8f9fa;
`;

const TopBar = styled.div`
  display: flex;
`;

function MainPresenter({ history }) {
  return (
    <>
      <Background>
        <TopBar>
          <BackButton history={history} />
          <div style={{}}>Chat</div>
        </TopBar>
        <Navigation />
      </Background>
    </>
  );
}

export default MainPresenter;
