import { useContext } from "react";
import { Navigate } from "react-router-dom";
import AuthContext from "./AuthContext";
import React from "react";
 
const ProtectedRoute = ({ children, accessBy }) => {
  const { user } = useContext(AuthContext);
 
  if (accessBy === "non-authenticated") {
    if (!user) {
      return children;
    }
  } else if (accessBy === "authenticated") {
    if (user) {
      return children;
    }
  } else if (accessBy === "adminonly") {
    if (user.role==="admin") {
      return children;
    } else {
      return <Navigate to="/"></Navigate>;
    }
  }
  return <Navigate to="/signin"></Navigate>;
};
export default ProtectedRoute;