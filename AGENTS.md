# Aura Repository Guidance

## Project context

- This is an Unreal Engine 5.6 C++ project.
- The runtime module is `Aura` under `Source/Aura`.
- Core systems include Gameplay Ability System (GAS), Enhanced Input, UMG, gameplay tags, and multiplayer replication.
- Follow the existing `Public`/`Private` source layout and Unreal naming conventions.

## Working conventions

- Keep changes focused on the requested task and preserve existing behavior unless the task explicitly requires a behavior change.
- Do not edit generated or transient directories such as `Binaries`, `DerivedDataCache`, `Intermediate`, `Saved`, `.vs`, or `.idea`.
- Do not modify binary assets under `Content` unless the task explicitly requires an asset change and the available tooling can edit the asset safely.
- Keep each `*.generated.h` include last in its header's include block.
- Preserve Unreal Header Tool compatibility for `UCLASS`, `USTRUCT`, `UENUM`, `UPROPERTY`, and `UFUNCTION` declarations.
- Prefer `TObjectPtr` for reflected UObject member references. Treat raw UObject pointers as non-owning and validate references before dereferencing when lifetime is not guaranteed.
- Avoid breaking Blueprint-facing names, signatures, categories, replication behavior, or serialized property layouts without explicitly calling out the migration impact.
- Keep module dependencies minimal and update `Aura.Build.cs` only when a new module is actually required.

## Gameplay Ability System and networking

- Verify that Ability System Component actor info is initialized for the correct owner and avatar at the correct lifecycle point.
- Treat gameplay state changes as server-authoritative unless the code is explicitly implementing prediction.
- Check replicated attributes and properties for matching lifetime registration, `ReplicatedUsing` handlers, and appropriate GAS notification macros.
- Check RPC ownership, authority guards, replication conditions, and client/server execution paths.
- Watch for delegate bindings that can outlive their owner, duplicate bindings, and missing cleanup.

## Verification

- Prefer targeted compilation or tests relevant to the changed module.
- Do not invent an Unreal Engine installation path. Use an existing project script or discoverable engine/tool path when available.
- If verification cannot be run in the current environment, state exactly what was not run and why.
- Do not launch the Unreal Editor or another GUI application unless the task explicitly requires it.

## Review guidelines

When reviewing a commit or pull request:

- Review the changed diff and enough surrounding code to validate behavior; do not review filenames in isolation.
- Prioritize correctness, regressions, crashes, undefined behavior, security, multiplayer desynchronization, and material performance problems.
- Pay particular attention to UObject/Actor lifetime, garbage collection, null validity, GAS effect and attribute behavior, replication and authority, RPC ownership, Blueprint compatibility, and expensive per-frame work.
- Report only actionable findings caused by the change. Do not report formatting-only issues, speculative concerns without a concrete failure mode, or pre-existing problems unrelated to the change.
- For each finding, include severity, file and line, the concrete failure scenario, and a concise remediation.
- Order findings by severity. If no actionable issue is found, state that clearly and mention any verification gaps.
- During a review task, do not modify source files, create commits, push branches, or open pull requests unless explicitly asked.
