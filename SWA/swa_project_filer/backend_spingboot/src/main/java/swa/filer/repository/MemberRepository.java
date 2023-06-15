package swa.filer.repository;

import java.util.List;
import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import swa.filer.models.Group;
import swa.filer.models.Member;
import swa.filer.models.User;

public interface MemberRepository extends JpaRepository<Member, Long>{
    
    List<Member> findAll();

    @Query("SELECT g FROM Group g JOIN Member m ON g.id = m.group.id WHERE m.user.id = ?1")
    List<Group> findGroupsOfUser(Long userId);

    @Query("SELECT u FROM User u JOIN Member m ON u.id = m.user.id WHERE m.group.id = ?1")
    List<User> findMembersOfGroup(Long id);

    @Query("SELECT m FROM Member m WHERE m.user.id = ?1 AND m.group.id = ?2")
    Optional<Member> findByUserAndGroup(Long userId, Long groupId);

    @Query("SELECT m FROM Member m WHERE m.group.id = ?1")
    List<Member> findByGroupId(Long groupId);

    @Query("SELECT m FROM Member m WHERE m.user.id = ?1")
    List<Member> findByUserId(Long userId);

}
