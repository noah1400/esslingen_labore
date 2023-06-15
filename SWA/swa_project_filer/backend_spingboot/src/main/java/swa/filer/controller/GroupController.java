package swa.filer.controller;

import java.util.List;
import java.util.Optional;

import javax.swing.text.html.Option;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import jakarta.validation.Valid;
import swa.filer.models.Group;
import swa.filer.models.Member;
import swa.filer.models.User;
import swa.filer.payload.request.CreateGroupRequest;

@RestController
public class GroupController extends ApiController{
    
    @GetMapping("/groups")
    public ResponseEntity<List<Group>> getGroups() {
        List<Group> groups = groupRepository.findAll();
        return ResponseEntity.ok(groups);
    }

    @GetMapping("/group/{group-id}")
    public ResponseEntity<Group> getGroupById(@PathVariable("group-id") String groupId) {
        Optional<Group> groupData = groupRepository.findById(Long.parseLong(groupId));
        if (groupData.isPresent()) {
            return ResponseEntity.ok(groupData.get());
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @GetMapping("/group/{group-id}/users")
    public ResponseEntity<List<User>> getGroupMembers(@PathVariable("group-id") String groupId) {
        // Get all users in group
        Optional<Group> groupData = groupRepository.findById(Long.parseLong(groupId));
        if (groupData.isPresent()) {
            Group group = groupData.get();
            List<User> users = memberRepository.findMembersOfGroup(group.getId());
            return ResponseEntity.ok(users);
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @GetMapping("/user/{user-id}/groups")
    public ResponseEntity<List<Group>> getUserGroups(@PathVariable("user-id") String userId) {
        // Get all groups for user
        Optional<User> userData = userRepository.findById(Long.parseLong(userId));
        if (userData.isPresent()) {
            User user = userData.get();
            List<Group> groups = memberRepository.findGroupsOfUser(user.getId());
            return ResponseEntity.ok(groups);
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @PostMapping("/user/{user-id}/join/{group-id}")
    public ResponseEntity<Group> joinGroup(@PathVariable("user-id") String userId, @PathVariable("group-id") String groupId) {
        // Add user to group
        Optional<User> userData = userRepository.findById(Long.parseLong(userId));
        Optional<Group> groupData = groupRepository.findById(Long.parseLong(groupId));
        if (userData.isPresent() && groupData.isPresent()) {
            User user = userData.get();
            Group group = groupData.get();
            memberRepository.save(new Member(user, group));
            return ResponseEntity.ok(group);
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @PostMapping("/user/{user-id}/leave/{group-id}")
    public ResponseEntity<Group> leaveGroup(@PathVariable("user-id") String userId, @PathVariable("group-id") String groupId) {
        // Remove user from group
        Optional<User> userData = userRepository.findById(Long.parseLong(userId));
        Optional<Group> groupData = groupRepository.findById(Long.parseLong(groupId));
        if (userData.isPresent() && groupData.isPresent()) {
            User user = userData.get();
            Group group = groupData.get();
            Optional<Member> memberData = memberRepository.findByUserAndGroup(user.getId(), group.getId());
            if (memberData.isPresent()) {
                Member member = memberData.get();
                memberRepository.delete(member);
                return ResponseEntity.ok(group);
            }
            return ResponseEntity.notFound().build();
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @PostMapping("/group/create")
    public ResponseEntity<Group> createGroup(@Valid @RequestBody CreateGroupRequest createGroupRequest) {
        // Create group
        String email = createGroupRequest.getEmail();
        Optional<User> userData = userRepository.findByEmail(email);
        if (!userData.isPresent()) {
            return ResponseEntity.notFound().build();
        }
        User founder = userData.get();
        Group group = new Group(founder, createGroupRequest.getGroupname());
        groupRepository.save(group);
        return ResponseEntity.ok(group);
    }

    @DeleteMapping("/group/{group-id}")
    public ResponseEntity<Group> deleteGroup(@PathVariable("group-id") String groupId) {
        // Delete group
        Optional<Group> groupData = groupRepository.findById(Long.parseLong(groupId));
        if (groupData.isPresent()) {
            Group group = groupData.get();

            // Delete all memberships of group
            List<Member> members = memberRepository.findByGroupId(group.getId());
            for (Member member : members) {
                memberRepository.delete(member);
            }

            groupRepository.delete(group);
            return ResponseEntity.ok(group);
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @PutMapping("/group/{group-id}")
    public ResponseEntity<Group> updateGroup(@PathVariable("group-id") String groupId, @Valid @RequestBody CreateGroupRequest createGroupRequest) {
        // Update group
        Optional<Group> groupData = groupRepository.findById(Long.parseLong(groupId));
        if (groupData.isPresent()) {
            Group group = groupData.get();
            group.setName(createGroupRequest.getGroupname());
            groupRepository.save(group);
            return ResponseEntity.ok(group);
        } else {
            return ResponseEntity.notFound().build();
        }
    }

}
