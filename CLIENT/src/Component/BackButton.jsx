/* eslint-disable react/prop-types */
import React from 'react';
import { AiOutlineLeft } from 'react-icons/ai';
import styled from 'styled-components';

const ImageButton = styled.button`
  position: relative;
  left: -16px;
  border: 0;
  outline: 0;
  background: #f8f9fa;
`;

function BackButton({ history }) {
  const goBack = () => {
    history.goBack();
  };
  return (
    <>
      <ImageButton onClick={goBack}>
        <AiOutlineLeft />
      </ImageButton>
    </>
  );
}

export default BackButton;
