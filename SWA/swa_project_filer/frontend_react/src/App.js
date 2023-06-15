import React from "react";
import { Route, Routes } from "react-router-dom";
import { AuthContextProvider } from "./components/shared/AuthContext";
import ProtectedRoute from "./components/shared/ProtectedRoute";
//Pages
import Home from './pages/Home';
import Signin from './pages/Signin';
import Signup from './pages/Signup';
import Usermanagement from "./pages/UserManagement";
import Groupmanagement from "./pages/GroupManagement";

function App() {
  return (
    <>
      <AuthContextProvider>
        <Routes>
          <Route path="/*" element={<ProtectedRoute accessBy="authenticated"><Home /></ProtectedRoute>} />
          <Route path="/manage/users" element={<ProtectedRoute accessBy="adminonly"><Usermanagement /></ProtectedRoute>} />
          <Route path="/manage/groups" element={<ProtectedRoute accessBy="adminonly"><Groupmanagement /></ProtectedRoute>} />
          <Route path="/signin" element={<ProtectedRoute accessBy="non-authenticated"><Signin /></ProtectedRoute>} />
          <Route path="/signup" element={<ProtectedRoute accessBy="non-authenticated"><Signup /></ProtectedRoute>} />
        </Routes>
      </AuthContextProvider>
    </>
  );
}
  
export default App;