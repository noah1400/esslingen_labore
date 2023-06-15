package swa.filer.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import swa.filer.repository.DirectoryRepository;
import swa.filer.repository.FileRepository;
import swa.filer.repository.GroupRepository;
import swa.filer.repository.MemberRepository;
import swa.filer.repository.UserRepository;



@RestController
@RequestMapping("/api")
public abstract class ApiController {

    @Autowired
    UserRepository userRepository;
    @Autowired
    DirectoryRepository directoryRepository;
    @Autowired
    FileRepository fileRepository;
    @Autowired
    GroupRepository groupRepository;
    @Autowired
    MemberRepository memberRepository;

}
