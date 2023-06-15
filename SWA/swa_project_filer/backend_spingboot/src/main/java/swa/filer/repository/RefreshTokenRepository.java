package swa.filer.repository;

import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;

import swa.filer.models.RefreshToken;
import swa.filer.models.User;


public interface RefreshTokenRepository extends JpaRepository<RefreshToken, Long>{

    Optional<RefreshToken> findByToken(String token);

    @Modifying
    int deleteByUser(User user);
}
