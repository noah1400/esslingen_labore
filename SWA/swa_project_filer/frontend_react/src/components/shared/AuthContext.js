import axios from "axios";
import React from "react";
import { createContext, useState } from "react";
import { useNavigate } from "react-router-dom";
 
const AuthContext = createContext();
 
export const AuthContextProvider = ({ children }) => {
  const [user, setUser] = useState(() => {
    let userProfle = sessionStorage.getItem("userProfile");
    if (userProfle) {
      return JSON.parse(userProfle);
    }
    return null;
  });
  const navigate = useNavigate();
  const login = async (payload) => {
    let logindata = await axios.post("/api/auth/signin", payload, {
      withCredentials: true,
    });
    let userdata = await axios.get("/api/user/"+logindata.data.id);
    sessionStorage.setItem("userProfile", JSON.stringify(userdata.data));
    setUser(userdata.data);
    navigate("/");
  };

  const signup = async (payload) => {
    await axios.post("/api/auth/signup", payload);
  };
  
  const signout = async () => {
    await axios.post("/api/auth/signout", {
      withCredentials: true,
    });
    sessionStorage.removeItem("userProfile");
    sessionStorage.removeItem("dirID");
    setUser(null);
    navigate("/login");
  };

  const getdirectories = async () => {
    const dirs = await axios.get(`/api/user/${user.id}/directory/`, {
      withCredentials: true,
    });
    return dirs;
  };

  const getdirectorybyname = async (directoryName) => {
    const dirs = await axios.get(`/api/user/${user.id}/directory/${directoryName}/id`, {
      withCredentials: true,
    });
    return dirs;
  };
  
  const getsubdirs = async (directoryId) => {
    const subdirs = await axios.get(`/api/user/${user.id}/directory/${directoryId}/subdir`, {
      withCredentials: true,
    });
    return subdirs;
  };

  const getfiles = async (directoryId) => {
    const subdirs = await axios.get(`/api/user/directory/${directoryId}/files`, {
      withCredentials: true,
    });
    return subdirs;
  };
  
  const deletefile = async (fileId) => {
    const subdirs = await axios.delete(`/api/user/directory/files/${fileId}`, {
      withCredentials: true,
    });
    return subdirs;
  };

  const createfile = async (directoryId, payload) => {
    const subdirs = await axios.post(`/api/user/${user.id}/directory/${directoryId}/files`, payload, {
      withCredentials: true,
    });
    return subdirs;
  };
  
  const getallusers = async () => {
    const userdata = await axios.get("/api/users", {
      withCredentials: true,
    });
    return userdata;
  };

  const edituser = async (userid, payload) => {
    const groupdata = await axios.put(`/api/user/${userid}/update`, payload, {
      withCredentials: true,
    });
    return groupdata;
  };
  
  const getallgroups = async () => {
    const groupdata = await axios.get("/api/groups", {
      withCredentials: true,
    });
    return groupdata;
  };
  
  const getusergroups = async () => {
    const groupdata = await axios.get(`/api/user/${user.id}/groups`, {
      withCredentials: true,
    });
    return groupdata;
  };
  
  const getgroupmembers = async (groupid) => {
    const groupdata = await axios.get(`/api/group/${groupid}/users`, {
      withCredentials: true,
    });
    return groupdata;
  };
  
  const addusertogroups = async (userid, groupid) => {
    const groupdata = await axios.post(`/api/user/${userid}/join/${groupid}`, {
      withCredentials: true,
    });
    return groupdata;
  };

  const editgroup = async (groupid, payload) => {
    const groupdata = await axios.put(`/api/group/${groupid}`, payload, {
      withCredentials: true,
    });
    return groupdata;
  };
  
  const removeuserfromgroups = async (userid, groupid) => {
    const groupdata = await axios.post(`/api/user/${userid}/leave/${groupid}`, {
      withCredentials: true,
    });
    return groupdata;
  };
  
  const deletegroups = async (groupid) => {
    const groupdata = await axios.delete(`/api/group/${groupid}`, {
      withCredentials: true,
    });
    return groupdata;
  };
  
  const creategroups = async (payload) => {
    const groupdata = await axios.post(`/api/group/create`, payload, {
      withCredentials: true,
    });
    return groupdata;
  };

  const createDirectory = async (payload, directoryId) => {
    const dirs = await axios.post(`/api/user/${user.id}/directory/${directoryId}`, payload, {
      withCredentials: true,
    });
    return dirs;
  };

  return (
    <>
      <AuthContext.Provider value={{ user, login, signout, signup, getallusers, edituser, 
        getdirectories, getsubdirs, createDirectory, getfiles, createfile, deletefile,getdirectorybyname,
        getallgroups, getusergroups, creategroups, getgroupmembers, addusertogroups, deletegroups, editgroup, removeuserfromgroups }}>
        {children}
      </AuthContext.Provider>
    </>
  );
};
 
export default AuthContext;