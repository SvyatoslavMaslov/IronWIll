// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (!ensure(LeftTrackToSet && RightTrackToSet)) {
		return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto ForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, ForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, ForwardIntention).Z;
	IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!ensure(LeftTrack && RightTrack)) {
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!ensure(LeftTrack && RightTrack)) {
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw) {
	if (!ensure(LeftTrack && RightTrack)) {
		return;
	}

	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

