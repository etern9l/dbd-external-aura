
namespace O {

	const uint32_t GWorld = 0xF2A8110; //48 89 4C 24 ? 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24
	const uint32_t GName = 0xF0633C0;  //ERROR_NAME_SIZE_EXCEEDED Const Wchar_t

	namespace UWorld {

		const uint32_t OwningGameInstance = 0x1C8;
		const uint32_t GameState = 0x168;
		const uint32_t Level = 0x180;
 		const uint32_t LevelSize = Level + 8;
		const uint32_t persistent_level = 0x38;

	}

	namespace ULevel {

		const uint32_t ActorArray = 0x0A0;
		const uint32_t ActorCount = ActorArray + 8;

	}

	namespace UGameInstance {

		const uint32_t LocalPlayers = 0x40;

	}

	namespace UPlayer {

		const uint32_t PlayerController = 0x38;
 
	}

	namespace APlayerController {

		const uint32_t AcknowledgedPawn = 0x350;
		const uint32_t PlayerCameraManager = 0x360;
 	
	}

	namespace APlayerCameraManager {

		const uint32_t POV = 0x22E0;
		const uint32_t DefaultFov = 0x2BC + 4;
		const uint32_t Ratio = 0x02CC + 4;

	}

	namespace FMinimalViewInfo {

		const uint32_t Location = 0x0;
		const uint32_t Rotation = 0x18;
		const uint32_t Fov = 0x30;
		const uint32_t DesiredFOV = 0x34;
		const uint32_t AspectRation = 0x48;

	}

	namespace AActor {

		const uint32_t RootComponent = 0x1A8;
 
	}

	namespace USceneComponent {

		const uint32_t RelativeScale3D = 0x170;
  		const uint32_t RelativeLocation = (RelativeScale3D - 0x18) - 0x18;
		const uint32_t ComponentToWorld = 0x260;

	}

	namespace ACharacter {

 		const uint32_t Mesh = 0x328;
 		const uint32_t CharacterMovement = 0x330;
 		const uint32_t CapsuleComponent = 0x338;

	}

	namespace USkeletalMeshComponent {

		const uint32_t LoDData = 0x630;

	}

	namespace APawn {

		const uint32_t PlayerState = 0x2B8;

	}

	namespace APlayerState {

		const uint32_t PlayerNamePrivate = 0x3A0;

	}

	namespace UCharacterMovement {
		const uint32_t MaxWalkSpeed = 0x218;
		const uint32_t MaxCustomMovementSpeed = 0x228;
	}

	namespace APallet {

		const uint32_t PalletState = 992; //bruteforce by value 0-4

	}

	namespace AGenerator {

		const uint32_t Percent = 960; //brutforce by value 0.85 in training

	}
 
 
	namespace UCapsuleComponent {

		const uint32_t CapsuleHalfHeight = 0x5B0;
		const uint32_t CapsuleRadius = 0x5B4;

	}

	const uint32_t SurvivorDBDOutline = 0x1CE8;
	const uint32_t KillerDBDOutline = 0x1C58;
	const uint32_t PalletDBDOutline = 0x5A0;
	const uint32_t GeneratorDBDOutline = 0x830;
	const uint32_t WindowDBDOutline = 0x4C8;
	const uint32_t MeatHookDBDOutline = 0x790;
	const uint32_t ChestDBDOutline = 0x530;

}