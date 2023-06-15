import React from 'react';
import ReactDOM from 'react-dom/client';
import { BrowserRouter } from "react-router-dom";
import App from "./App";
//Style
import "./App.css"
import "fastbootstrap/dist/css/fastbootstrap.min.css"
import "fastbootstrap/dist/js/fastbootstrap.min.js"
//
const root = ReactDOM.createRoot(document.getElementById("root"));
root.render(
  <BrowserRouter>
    <App />
  </BrowserRouter>
);