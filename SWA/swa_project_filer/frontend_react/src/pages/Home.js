import React, { useState, useEffect, useContext, useRef } from 'react'
import NavigationComponent from '../components/Navigation';
import UploadBar from '../components/UploadBar';
import SideNav from '../components/SideNav';
import Item from '../components/items/Item';
import FileInfo from '../components/FileInfo';
import AuthContext from "../components/shared/AuthContext";

const Home = () => {
    const { getdirectories, getsubdirs,getfiles, getdirectorybyname } = useContext(AuthContext);  
    const [selectedfile, setSelectedFile] = useState(null);
    const [alldirectories, setAllDirectories] = useState(null);
    const [currentdirectory, setCurrentDirectory] = useState(new Array());
    const [currentfiles, setCurrentFiles] = useState(new Array());

    function test(e) {
        console.log(e);
        if (e!==false) {
            setSelectedFile(e);
        } else {
            setSelectedFile(null);
        }
    }
    
    useEffect(() => {
        //Get Current Directory
        const path = window.location.pathname.split("/");
        const lastfolder = path[path.length-1] ==='' ? null : path[path.length-1];
        let dirid = null;
        const subdirs = async function () {
            if (lastfolder!==null) {
                await getdirectorybyname(lastfolder).then((result) => {
                    dirid = (result!==undefined) ? result.data[0].dirID : null;
                    sessionStorage.setItem("dirID", dirid)     
                });
            }
            await getsubdirs(lastfolder).then((result) => {
                console.log(result.data);
                setCurrentDirectory(result.data);
            }).catch((err) => {
                console.log(err);
            });
            await getfiles(dirid).then((result) => {
                setCurrentFiles(result.data);                
            }).catch((err) => {
                console.log(err);
            });
        }
        subdirs();
    }, []);

    

    return (
        <div className='vh-100'>
            <NavigationComponent />
            <div className='row w-100 content-fill'>
                <SideNav/>
                <div className='col-8'>
                    <UploadBar />
                    {/* File List Header*/}
                    <div className='row border-bottom mb-2 mx-2'>
                        <div className='col-md-7 offset-md-1'><p className='mb-0 fw-semibold'>Name</p></div>
                        <div className='col-md-4'><p className='mb-0 fw-semibold'>Modified</p></div>
                    </div>
                    {/* File List Items*/}
                    <div className='row border-bottom m-0 mx-2'>
                        {
                            currentdirectory.map((dir, index)=>{
                                return <Item type="folder" key={index} name={dir.name} modifydate={dir.updated_at} subdir={dir.subdir_id} group={dir.group_id} id={dir.dirID} onselected={test}/>
                            })
                        }
                        {
                            currentfiles.map((dir, index)=>{
                                return <Item type="file" key={index} name={dir.filename} modifydate={dir.updated_at} subdir={dir.subdir_id} group={dir.group_id} id={dir.fileID} onselected={test}/>
                            })
                        }
                    </div>
                </div>
                <div className='col-2 border-start'>
                    {
                        (selectedfile===null) ? <FileInfo /> : <FileInfo data={selectedfile} />
                    }
                </div>
            </div>
        </div>
    );
}

export default Home;